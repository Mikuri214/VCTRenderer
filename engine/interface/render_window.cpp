#include "stdafx.h"
#include "render_window.h"

void RenderWindow::onErrorCallback(int code, const char * description)
{
    throw std::runtime_error(description);
}

int RenderWindow::Open()
{
    // glfw error catching
    glfwSetErrorCallback(RenderWindow::onErrorCallback);

    if(isOpen || !glfwInit()) return 1;

    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, false);
    this->windowHandler = glfwCreateWindow(this->settings.width,
                                           this->settings.height,
                                           this->settings.title.c_str(),
                                           nullptr, nullptr);
    glfwGetWindowPos(this->windowHandler, &this->settings.position.first,
                     &this->settings.position.second);

    if(!this->windowHandler)
    {
        glfwTerminate();
        return 2;
    }

// successfull window open
    this->isOpen = true;
    return 0;
}

void RenderWindow::Destroy()
{
    glfwDestroyWindow(this->windowHandler);
}

void RenderWindow::SetPosition(const int x, const int y)
{
    glfwSetWindowPos(this->windowHandler, x, y);
    this->settings.position.first = x;
    this->settings.position.second = y;
}

void RenderWindow::SetAsCurrentContext()
{
    glfwMakeContextCurrent(this->windowHandler);
}

RenderWindow::RenderWindow()
{
}

RenderWindow::~RenderWindow()
{
    glfwDestroyWindow(this->windowHandler);
    glfwMakeContextCurrent(this->windowHandler);
}