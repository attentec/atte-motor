#ifndef GRAPHICS_SYSTEM_H
#define GRAPHICS_SYSTEM_H

#include <algorithm>
#include <functional>
#include <experimental/optional>
#include <vector>

#include "entity_component_system.h"

struct GraphicsComponent {
    int model;
};

class GraphicsSystem {
    private:
        int component_id_counter;
        std::vector<std::pair<ComponentId, GraphicsComponent>> components;
    public:
        GraphicsSystem() : component_id_counter(0) {}

        void update() {
            for (auto& component_pair : components) {
                component_pair.second.model += 1;
            }
        }

        ComponentId create_component() {
            auto id = ComponentId { component_id_counter++ };
            components.push_back(std::make_pair(id, GraphicsComponent{}));
            return id;
        }

        std::experimental::optional<GraphicsComponent*> get_component(ComponentId id) {
            auto it = std::find_if(components.begin(), components.end(), [id](const auto& a) {
                    return a.first == id;
                    });

            return it != components.end() ? std::experimental::make_optional(&it->second) : std::experimental::nullopt;
        }
};

#endif
