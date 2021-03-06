/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2012.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include <boost/foreach.hpp>

#include <fwServices/macros.hpp>

#include <fwData/Image.hpp>

#include <fwComEd/ImageMsg.hpp>
#include <fwComEd/helper/Image.hpp>
#include <fwComEd/fieldHelper/MedicalImageHelpers.hpp>

#include "ctrlSelection/MedicalImageSrv.hpp"

namespace ctrlSelection
{

//-----------------------------------------------------------------------------

fwServicesRegisterMacro( ::fwServices::IController, ::ctrlSelection::MedicalImageSrv, ::fwData::Image ) ;

//-----------------------------------------------------------------------------

MedicalImageSrv::MedicalImageSrv() throw()
{
    //addNewHandledEvent(::fwComEd::ImageMsg::BUFFER );
}

//-----------------------------------------------------------------------------

MedicalImageSrv::~MedicalImageSrv() throw()
{}

//-----------------------------------------------------------------------------

void MedicalImageSrv::receiving( ::fwServices::ObjectMsg::csptr message ) throw ( ::fwTools::Failed )
{
    SLM_TRACE_FUNC();
    if(message->hasEvent(::fwComEd::ImageMsg::BUFFER))
    {
        this->convertImage();
    }
}

//-----------------------------------------------------------------------------

void MedicalImageSrv::convertImage()
{
    ::fwData::Image::sptr pImg = this->getObject< ::fwData::Image >();
    if(::fwComEd::fieldHelper::MedicalImageHelpers::checkImageValidity(pImg))
    {
        ::fwComEd::helper::Image helper ( pImg );

        helper.createLandmarks();
        helper.createTransferFunctionPool(this->getSptr());
        helper.createImageSliceIndex();
    }
}

//-----------------------------------------------------------------------------

void MedicalImageSrv::starting()  throw ( ::fwTools::Failed )
{
    this->convertImage();
}

//-----------------------------------------------------------------------------

void MedicalImageSrv::stopping()  throw ( ::fwTools::Failed )
{}

//-----------------------------------------------------------------------------

void MedicalImageSrv::swapping()  throw ( ::fwTools::Failed )
{
    this->convertImage();
}

//-----------------------------------------------------------------------------

void MedicalImageSrv::configuring()  throw ( ::fwTools::Failed )
{}

//-----------------------------------------------------------------------------

void MedicalImageSrv::reconfiguring()  throw ( ::fwTools::Failed )
{}

//-----------------------------------------------------------------------------

void MedicalImageSrv::updating() throw ( ::fwTools::Failed )
{}

//-----------------------------------------------------------------------------

void MedicalImageSrv::info( std::ostream &_sstream )
{}

//-----------------------------------------------------------------------------

} // ctrlSelection
