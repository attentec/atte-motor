#ifndef ENTITY_H
#define ENTITY_H

#include <experimental/optional>
#include <algorithm>
#include <vector>

#include "entity_component_system.h"

class Entity {
    public:
        std::experimental::optional<ComponentId> get_component(SystemId system_id) {
            auto it = std::find_if(components.begin(), components.end(), [system_id] (const auto& p) {
                    return p.first == system_id;
                    });
            return it != components.end() ? std::experimental::make_optional(it->second) : std::experimental::nullopt;
        }

        void add_component(SystemId system_id, ComponentId component_id) {
            components.push_back(std::make_pair(system_id, component_id));
        }

    private:
        std::vector<std::pair<SystemId, ComponentId>> components;
};

#endif
