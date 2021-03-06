/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2012.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef _FWGUIQT_LAYOUTMANAGER_FRAMELAYOUTMANAGER_HPP_
#define _FWGUIQT_LAYOUTMANAGER_FRAMELAYOUTMANAGER_HPP_

#include <QPointer>
#include <QObject>
#include <QPoint>

#include <fwCore/base.hpp>

#include <fwGui/layoutManager/IFrameLayoutManager.hpp>

#include "fwGuiQt/container/QtContainer.hpp"
#include "fwGuiQt/config.hpp"

QT_BEGIN_NAMESPACE
class QMainWindow;
QT_END_NAMESPACE

namespace fwGui
{

/**
 * @brief   Defines the frame manager.
 * @class   FrameLayoutManager
 * 
 * @date    2009-2010.
 *
 */
class FWGUIQT_CLASS_API FrameLayoutManager : public QObject, public ::fwGui::layoutManager::IFrameLayoutManager
{
    Q_OBJECT
public:

    fwCoreClassDefinitionsWithFactoryMacro( (FrameLayoutManager)(::fwGui::layoutManager::IFrameLayoutManager),
                                            (()),
                                            ::fwGui::factory::New< FrameLayoutManager > );

    FWGUIQT_API FrameLayoutManager(::fwGui::GuiBaseObject::Key key);

    FWGUIQT_API virtual ~FrameLayoutManager();

    /**
     * @brief Instantiate frame.
     */
    FWGUIQT_API virtual void createFrame();

    /**
     * @brief Destroy local frame with sub containers.
     */
    FWGUIQT_API virtual void destroyFrame();

private Q_SLOTS:
    void onCloseFrame();

private:

    void setState(FrameState state);
    FrameState getState();
    bool isOnScreen(const QPoint& pos);

    QPointer<QMainWindow> m_qtWindow;
};

} // namespace fwGui

#endif /*_FWGUIQT_LAYOUTMANAGER_FRAMELAYOUTMANAGER_HPP_*/


