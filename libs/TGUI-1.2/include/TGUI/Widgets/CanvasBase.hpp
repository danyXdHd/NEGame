/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2024 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef TGUI_CANVAS_BASE_HPP
#define TGUI_CANVAS_BASE_HPP

#include <TGUI/Widgets/ClickableWidget.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TGUI_MODULE_EXPORT namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// This class is used as base class for the backend-specific canvas widgets
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API CanvasBase : public ClickableWidget
    {
    public:

        using Ptr = std::shared_ptr<CanvasBase>; //!< Shared widget pointer
        using ConstPtr = std::shared_ptr<const CanvasBase>; //!< Shared constant widget pointer

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /// @brief Constructor
        /// @param typeName     Type of the widget
        /// @param initRenderer Should the renderer be initialized? Should be true unless a derived class initializes it.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        CanvasBase(const char* typeName, bool initRenderer);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets whether the widget should completely ignore mouse events and let them pass to the widgets behind it
        ///
        /// @param ignore  Should mouse events be ignored by this widget?
        ///
        /// By default, mouse events are NOT ignored.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void ignoreMouseEvents(bool ignore = true);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether the widget is ignoring mouse events and letting them pass to the widgets behind it
        ///
        /// @return Are mouse events ignored by this widget?
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD bool isIgnoringMouseEvents() const;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether the widget can gain focus
        /// @return Can the widget be focused?
        ///
        /// This function returns false for Canvas widgets.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD bool canGainFocus() const override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether the mouse position (which is relative to the parent widget) lies on top of the widget
        /// @return Is the mouse on top of the widget?
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD bool isMouseOnWidget(Vector2f pos) const override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Saves the widget as a tree node in order to save it to a file
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD std::unique_ptr<DataIO::Node> save(SavingRenderersMap& renderers) const override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Loads the widget from a tree of nodes
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void load(const std::unique_ptr<DataIO::Node>& node, const LoadingRenderersMap& renderers) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    private:

        bool m_ignoringMouseEvents = false;
    };
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_CANVAS_BASE_HPP
