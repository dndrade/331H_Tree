#pragma once
#include <memory>

template<typename T>
struct Node
{
    std::shared_ptr<T> data = nullptr;
    std::shared_ptr<Node> left = nullptr;
    std::shared_ptr<Node> right = nullptr;
};
