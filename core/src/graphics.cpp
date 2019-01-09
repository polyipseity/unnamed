#include "graphics.h"
#include "utilities/logging.h"

#define GRAPHICS_ID string_("Graphics")

#if PLATFORM_WINDOWS
#include <Windows.h>
#include <WinUser.h>
#endif /* PLATFORM_WINDOWS */
#if WIDE_STRING
#include <sstream>
#endif /* WIDE_STRING */
#include <stdexcept>

#if PLATFORM_MACOS

#elif PLATFORM_LINUX /* PLATFORM_MACOS */

#elif PLATFORM_WINDOWS /* PLATFORM_LINUX */
#define VIRTUAL_X GetSystemMetrics(SM_CXVIRTUALSCREEN)
#define VIRTUAL_Y GetSystemMetrics(SM_CYVIRTUALSCREEN)
#define PRIMARY_X GetSystemMetrics(SM_CXSCREEN)
#define PRIMARY_Y GetSystemMetrics(SM_CYSCREEN)
#endif /* PLATFORM_WINDOWS */

using logLevel = logging::Level;

namespace graphics
{
#if GL_GRAPHICS
    bool glfwUnsupported = false;
    GLFWmonitor* monitor;
    GLFWwindow* window;
    GLuint vertexBuffer;

    void createWindow()
    {
        glfwSetErrorCallback(glfwErrorCallback);

        logging::printlnf(logLevel::LEVEL_INFO, GRAPHICS_ID, SECTION_HEADER_NAMED, string_("GLFW"));
        logging::printlnf(logLevel::LEVEL_INFO, GRAPHICS_ID, string_("Compiled-time version: %i.%i.%i"), GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR, GLFW_VERSION_REVISION);
        int major, minor, revision;
        glfwGetVersion(&major, &minor, &revision);
        logging::printlnf(logLevel::LEVEL_INFO, GRAPHICS_ID, string_("Runtime version: %i.%i.%i"), major, minor, revision);
        if (GLFW_VERSION_MAJOR != major || GLFW_VERSION_MINOR != minor || GLFW_VERSION_REVISION != revision)
        {
            glfwUnsupported = true;
            logging::printlnf(logLevel::LEVEL_WARNING, GRAPHICS_ID, string_("Compiled-time version and runtime version differs."));
            logging::printlnf(logLevel::LEVEL_WARNING, GRAPHICS_ID, string_("No support is provided by using a different version of GLFW!"));
        }
        logging::printlnf(logLevel::LEVEL_INFO, GRAPHICS_ID, SECTION_FOOTER);

        if (!glfwInit())
        {
            logging::printlnf(logLevel::LEVEL_FATAL, GRAPHICS_ID, string_("Failed to initialize glfw!"));
            throw std::runtime_error("Failed to initialize glfw!");
        }

        // Require the OpenGL context to support OpenGL 3.2 at the least.
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        logging::printlnf(logLevel::LEVEL_INFO, GRAPHICS_ID, SECTION_HEADER_NAMED, string_("Monitors Information"));
#if PLATFORM_WINDOWS
        logging::printlnf(logLevel::LEVEL_INFO, GRAPHICS_ID, string_("Virtual Monitor Size: (%d, %d)"), VIRTUAL_X, VIRTUAL_Y);
        logging::printlnf(logLevel::LEVEL_INFO, GRAPHICS_ID, string_("Primary Monitor Size: (%d, %d)"), PRIMARY_X, PRIMARY_Y);
        logging::printlnf(logLevel::LEVEL_INFO, GRAPHICS_ID, string_("Primary Monitor Work Area: %d"), GetSystemMetrics(SPI_GETWORKAREA));
#endif /* PLATFORM_WINDOWS */
        logging::printlnf(logLevel::LEVEL_INFO, GRAPHICS_ID, SECTION_FOOTER);

        window = glfwCreateWindow(PRIMARY_X, PRIMARY_Y, NAME, glfwGetPrimaryMonitor(), nullptr);
        glfwMakeContextCurrent(window);
    }

    void glInit()
    {
        glewExperimental = GL_TRUE;
        glewInit();
        glGenBuffers(1, &vertexBuffer);
    }

    void glfwErrorCallback(int error, const char* description)
    {
#if WIDE_STRING
        std::wostringstream woss;
        woss << description;
        logging::printlnf(logLevel::LEVEL_ERROR, string_("GLFW"), string_("An error occured. Code: %i, Description: %s"), error, woss.str().c_str());
#else /* WIDE_STRING */
        logging::printlnf(logLevel::LEVEL_ERROR, string_("GLFW"), string_("An error occured. Code: %i, Description: %s"), error, description);
#endif
    }

#elif GLES_GRAPHICS /* GL_GRAPHICS */

#elif METAL_GRAPHICS /* GLES_GRAPHICS */

#endif /* METAL_GRAPHICS*/
}