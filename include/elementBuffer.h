#ifndef ELEMENT_BUFFER_H
#define ELEMENT_BUFFER_H
// #pragma once
#include <assert_utils.h>

class ElementBuffer{
private:
    unsigned int m_RenderID;
    unsigned int m_Count;
public:
    ElementBuffer(const int* data, unsigned int count);
    ~ElementBuffer();

    void Bind() const;
    void UnBind() const;
};
#endif