#ifndef ELEMENT_BUFFER_H
#define ELEMENT_BUFFER_H
// #pragma once
#include <assert_utils.h>
#include <vector>
    // std::vector<unsigned int> m_Indices;
class ElementBuffer{
private:
    unsigned int m_RenderID;
    unsigned int m_Count;
public:
    ElementBuffer(const unsigned int* data, unsigned int count);
    ElementBuffer(const std::vector<unsigned int> data);
    ~ElementBuffer();

    void Bind() const;
    void UnBind() const;
    inline unsigned int getCount()const {return m_Count;};
};
#endif