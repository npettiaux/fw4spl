/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2013.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include <QColor>
#include <QColorDialog>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QPixmap>
#include <QStyle>

#include <fwCore/base.hpp>

#include <fwData/Reconstruction.hpp>
#include <fwData/Material.hpp>
#include <fwData/Mesh.hpp>

#include <fwComEd/MaterialMsg.hpp>

#include <fwRuntime/ConfigurationElement.hpp>
#include <fwRuntime/operations.hpp>

#include <fwServices/Base.hpp>
#include <fwServices/macros.hpp>
#include <fwServices/registry/ObjectService.hpp>
#include <fwServices/IService.hpp>
#include <fwServices/op/Get.hpp>
#include <fwServices/IEditionService.hpp>

#include <fwGuiQt/container/QtContainer.hpp>

#include "uiReconstructionQt/OrganMaterialEditor.hpp"

namespace uiReconstruction
{

fwServicesRegisterMacro( ::gui::editor::IEditor , ::uiReconstruction::OrganMaterialEditor , ::fwData::Reconstruction ) ;


OrganMaterialEditor::OrganMaterialEditor() throw()
{
    //handlingEventOff();
}

//------------------------------------------------------------------------------

OrganMaterialEditor::~OrganMaterialEditor() throw()
{}

//------------------------------------------------------------------------------

void OrganMaterialEditor::starting() throw(::fwTools::Failed)
{
    SLM_TRACE_FUNC();
    this->create();
    ::fwGuiQt::container::QtContainer::sptr qtContainer =  ::fwGuiQt::container::QtContainer::dynamicCast( this->getContainer() );
    QWidget* const container = qtContainer->getQtContainer();
    SLM_ASSERT("container not instanced", container);

    m_colourButton = new QPushButton(tr("Color"), container) ;
    m_colourButton->setToolTip(tr("Selected organ's color"));
    m_colourButton->setMinimumSize (m_colourButton->sizeHint());
//    m_colourButton->setMinimumSize (120,35);

    QLabel* transparencyLabel = new QLabel(tr("Transparency : "), container);
    m_opacitySlider = new QSlider( Qt::Horizontal, container) ;
    m_opacitySlider->setToolTip(tr("Selected organ's opacity"));
    m_opacitySlider->setRange(0,100);
    m_opacitySlider->setTickInterval(20);
    m_opacitySlider->setTickPosition(QSlider::TicksBelow);
    m_opacitySlider->setMinimumSize (m_opacitySlider->sizeHint());

    m_transparencyValue = new QLabel("", container);
    m_transparencyValue->setMinimumSize (m_transparencyValue->sizeHint());

    QVBoxLayout* layout = new QVBoxLayout(container);
    layout->addWidget( m_colourButton, 0 ) ;

    QHBoxLayout* transparencyLayout= new QHBoxLayout( container );
    transparencyLayout->addWidget( transparencyLabel, 0) ;
    transparencyLayout->addWidget( m_opacitySlider, 1 );
    transparencyLayout->addWidget( m_transparencyValue, 0) ;
    layout->addLayout( transparencyLayout, 0) ;

    container->setLayout( layout );
    container->setEnabled(false);

    QObject::connect(m_opacitySlider, SIGNAL(valueChanged( int )), this, SLOT(onOpacitySlider( int )));
    QObject::connect(m_colourButton, SIGNAL(clicked ()), this, SLOT(onColorButton( )));

    this->updating();
}

//------------------------------------------------------------------------------

void OrganMaterialEditor::stopping() throw(::fwTools::Failed)
{
    SLM_TRACE_FUNC();

    QObject::disconnect(m_opacitySlider, SIGNAL(valueChanged( int )), this, SLOT(onOpacitySlider( int )));
    QObject::disconnect(m_colourButton, SIGNAL(clicked ()), this, SLOT(onColorButton( )));

    this->getContainer()->clean();
    this->destroy();
}

//------------------------------------------------------------------------------

void OrganMaterialEditor::configuring() throw(fwTools::Failed)
{
    SLM_TRACE_FUNC();
    this->initialize();
}

//------------------------------------------------------------------------------

void OrganMaterialEditor::updating() throw(::fwTools::Failed)
{
    this->refreshMaterial();
}

//------------------------------------------------------------------------------

void OrganMaterialEditor::swapping() throw(::fwTools::Failed)
{
    this->updating();
}

//------------------------------------------------------------------------------

void OrganMaterialEditor::receiving( ::fwServices::ObjectMsg::csptr _msg ) throw(::fwTools::Failed)
{
}

//------------------------------------------------------------------------------

void OrganMaterialEditor::info( std::ostream &_sstream )
{
}

//------------------------------------------------------------------------------

void OrganMaterialEditor::onColorButton()
{
    ::fwData::Reconstruction::sptr reconstruction = this->getObject< ::fwData::Reconstruction>();
    SLM_ASSERT("No Reconstruction!", reconstruction);

    ::fwData::Material::sptr material = reconstruction->getMaterial() ;
    int red = material->ambient()->red()*255;
    int green = material->ambient()->green()*255;
    int blue = material->ambient()->blue()*255;

    // Create Color choice dialog.
    ::fwGuiQt::container::QtContainer::sptr qtContainer =  ::fwGuiQt::container::QtContainer::dynamicCast( this->getContainer() );
    QWidget* const container = qtContainer->getQtContainer();
    SLM_ASSERT("container not instanced", container);

    QColor oldColor(red, green, blue);
    QColor color = QColorDialog::getColor(oldColor, container);
    if(color.isValid())
    {
        material->ambient()->red() = color.redF();
        material->ambient()->green() = color.greenF();
        material->ambient()->blue() = color.blueF();
        this->materialNotification();
        refreshMaterial();
    }

}

//------------------------------------------------------------------------------

void OrganMaterialEditor::onOpacitySlider(int value )
{
    ::fwData::Reconstruction::sptr reconstruction = this->getObject< ::fwData::Reconstruction>();
    SLM_ASSERT("No Reconstruction!", reconstruction);

    ::fwData::Material::sptr material = reconstruction->getMaterial() ;
    material->ambient()->alpha() = value/100.0;
    std::stringstream ss;
    ss << value << "%";
    m_transparencyValue->setText(QString::fromStdString(ss.str()));

    this->materialNotification();
}

//------------------------------------------------------------------------------

void OrganMaterialEditor::refreshMaterial( )
{
    ::fwData::Reconstruction::sptr reconstruction = this->getObject< ::fwData::Reconstruction>();
    SLM_ASSERT("No Reconstruction!", reconstruction);

    ::fwGuiQt::container::QtContainer::sptr qtContainer =  ::fwGuiQt::container::QtContainer::dynamicCast( this->getContainer() );
    QWidget* const container = qtContainer->getQtContainer();
    SLM_ASSERT("container not instanced", container);

    container->setEnabled(!reconstruction->getOrganName().empty());

    ::fwData::Material::sptr material = reconstruction->getMaterial() ;
    QColor materialColor = QColor (
                material->ambient()->red()*255,
                material->ambient()->green()*255,
                material->ambient()->blue()*255,
                material->ambient()->alpha()*255
                );

    int iconSize = m_colourButton->style()->pixelMetric(QStyle::PM_LargeIconSize);
    QPixmap pix(iconSize, iconSize);
    pix.fill(materialColor);

    m_colourButton->setIcon(QIcon(pix));

    int a = material->ambient()->alpha()*100;
    m_opacitySlider->setValue( a ) ;
    std::stringstream ss;
    ss << a << "%";
    m_transparencyValue->setText(QString::fromStdString(ss.str()));
}

//------------------------------------------------------------------------------

void OrganMaterialEditor::materialNotification( )
{
    ::fwData::Reconstruction::sptr reconstruction = this->getObject< ::fwData::Reconstruction>();
    SLM_ASSERT("No Reconstruction!", reconstruction);

    ::fwComEd::MaterialMsg::sptr msg = ::fwComEd::MaterialMsg::New();
    msg->addEvent( ::fwComEd::MaterialMsg::MATERIAL_IS_MODIFIED ) ;
    ::fwServices::IEditionService::notify(this->getSptr(), reconstruction->getMaterial(), msg);
}

//------------------------------------------------------------------------------

}

