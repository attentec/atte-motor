#ifndef ENTITY_COMPONENT_SYSTEM_H
#define ENTITY_COMPONENT_SYSTEM_H

struct ComponentId
{
    int value; 
    explicit ComponentId(int value) : value(value) {}
};

struct SystemId
{
    short value;
    explicit SystemId(short value) : value(value) {}
};

bool operator==(const ComponentId a, const ComponentId b)
{
    return a.value == b.value;
}

bool operator==(const SystemId a, const SystemId b)
{
    return a.value == b.value;
}

const SystemId GRAPHICS_SYSTEM_ID = SystemId{0};


#endif
