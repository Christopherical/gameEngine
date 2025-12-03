#pragma once

#include <unordered_map>

#include "Utils/InputBindings.hpp"


class InputManager
{
private:
    std::unordered_multimap<int, Input::Binding> bindings_;

public:
    void Bind(int action, const Input::Binding& binding);
    bool Pressed(int action) const;
    void Clear();

private:
    bool Pressed(const Input::Keyboard& key) const;
    bool Pressed(const Input::Mouse& button) const;
    bool Pressed(const Input::Gamepad& button) const;
    bool Pressed(const Input::Axis& axis) const;
};