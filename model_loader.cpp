#include "model_loader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

struct ParserState
{
  Buffer buffer;
  size_t index;

  ParserState(Buffer buffer, size_t index) : buffer(buffer), index(index) {}

  ParserState update(size_t new_index) {
    return ParserState(buffer, new_index);
  }
};

template <class T>
struct ParserResult
{
  ParserState state;
  T t;

  ParserResult(Buffer buffer, size_t index, T t) : state(buffer, index), t(t) {}
  ParserResult(ParserState state, T t) : state(state), t(t) {}
};

ParserState skip_line(ParserState state)
{
  auto index = state.index;
  while (index < state.buffer.size && state.buffer[index] != '\n')
  {
    index += 1;
  }
  return state.update(index);
}
bool buffer_starts_with(ParserState state, const char* str)
{
  if (*str == '\0') { return true; }
  return state.buffer[state.index] == *str && buffer_starts_with(state.update(state.index + 1), str+1);
}
ParserState skip_constant(ParserState state, const char* constant)
{
  return state.update(state.index + strlen(constant));
}

ParserState skip_comments(ParserState state)
{
  if (buffer_starts_with(state, "#"))
  {
    return skip_line(state);
  }
  return state;
}

ParserState skip_white_space(ParserState state)
{
  auto index = state.index;
  while (index < state.buffer.size)
  {
    switch (state.buffer[index])
    {
      case ' ':
      case '\n':
      case '\t':
      index += 1;
      continue;
      default:
      return state.update(index);
    }
  }
  return state.update(index);
}

ParserState skip_white_space_and_comments(ParserState state)
{
  auto other_index = state.index + 1;
  while (other_index != state.index)
  {
    other_index = state.index;
    state = skip_white_space(state);
    state = skip_comments(state);
  }
  return state;
}


ParserState skip_mtllib_stuff(ParserState state)
{
  if (buffer_starts_with(state, "mtllib"))
  {
    return skip_line(state);
  }
  return state;
}

ParserState skip_g_thing(ParserState state)
{
  if (buffer_starts_with(state, "g"))
  {
    return skip_line(state);
  }
  return state;
}

struct Vertex
{
  float x;
  float y;
  float z;
};

ParserResult<Vertex> read_vertex(ParserState state) {
  // Skip vertex metadata
  state = skip_constant(state, "v");
  state = skip_white_space(state);

  // read xyz
  Vertex v;
  sscanf((const char *)(state.buffer.data + state.index), "%f %f %f\n", &v.x, &v.y, &v.z);
  return ParserResult<Vertex>(skip_line(state), v);
}

ParserResult<std::vector<Vertex>> read_vertices(ParserState state) {
  // Find them all v's
  std::vector<Vertex> vertices;
  while(buffer_starts_with(state, "v ")) {
    auto result = read_vertex(state);
    vertices.push_back(result.t);
    state = skip_white_space(result.state);
  }
  return ParserResult<std::vector<Vertex>>(state, vertices);
}

Model parse(Buffer buffer) {
  ParserState state(buffer, 0);

  state = skip_white_space_and_comments(state);

  // Skip first texts
  state = skip_mtllib_stuff(state);
  state = skip_white_space_and_comments(state);
  state = skip_g_thing(state);
  state = skip_white_space_and_comments(state);

  // Read vertices
  auto vertice_parse_result = read_vertices(state);
  for(auto vertex: vertice_parse_result.t) {
    printf("%f %f %f \n", vertex.x, vertex.y, vertex.z);
  }
  state = vertice_parse_result.state;

  fwrite(state.buffer.data + state.index, 1, state.buffer.size - state.index, stdout);
  return Model();
}
