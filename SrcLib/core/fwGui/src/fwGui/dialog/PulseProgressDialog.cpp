/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2012.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */


#include "fwGui/dialog/PulseProgressDialog.hpp"

namespace fwGui
{
namespace dialog
{
//-----------------------------------------------------------------------------

PulseProgressDialog::PulseProgressDialog( const std::string &title, ::fwGui::dialog::IPulseProgressDialog::Stuff stuff, const std::string &msg, ::fwGui::dialog::IPulseProgressDialog::MilliSecond frequenceRefresh )
{
    ::fwGui::GuiBaseObject::sptr guiObj = ::fwGui::factory::New(IPulseProgressDialog::REGISTRY_KEY);
    m_implementation = ::fwGui::dialog::IPulseProgressDialog::dynamicCast(guiObj);
    if (m_implementation)
    {
        m_implementation->setStuff(stuff);
        m_implementation->setTitle(title);
        m_implementation->setMessage(msg);
        m_implementation->setFrequence(frequenceRefresh);
    }
    else
    {
        this->setStuff(stuff);
    }
}

//-----------------------------------------------------------------------------

void PulseProgressDialog::setTitle(const std::string &title)
{
    if (m_implementation)
    {
        m_implementation->setTitle(title);
    }
}

//-----------------------------------------------------------------------------

void PulseProgressDialog::setMessage(const std::string &msg)
{
    if (m_implementation)
    {
        m_implementation->setMessage(msg);
    }
}

//-----------------------------------------------------------------------------

void PulseProgressDialog::show()
{
    if (m_implementation)
    {
        m_implementation->show();
    }
    else
    {
        m_stuff();
    }
}

//-----------------------------------------------------------------------------

} //namespace dialog
} //namespace fwGui
