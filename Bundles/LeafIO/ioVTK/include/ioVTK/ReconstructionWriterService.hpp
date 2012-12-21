/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2012.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef _IOVTK_RECONSTRUCTIONWRITERSERVICE_HPP_
#define _IOVTK_RECONSTRUCTIONWRITERSERVICE_HPP_

#include <string>
#include <boost/filesystem/path.hpp>

#include <io/IWriter.hpp>


#include "ioVTK/export.hpp"

namespace fwData
{
    class Acquisition;
}


namespace ioVTK
{
/**
 * @brief   Reconstruction writer service.
 * @class   ReconstructionWriterService.
 * @author  IRCAD (Research and Development Team).
 * @date    2009.
 *
 * Service reading a VTK image using the vtkIO lib.
 *
 * Service registered details : \n
 * fwServicesRegisterMacro( ::io::IWriter , ::ioVTK::ReconstructionWriterService , ::fwData::Acquisition )
 */
class IOVTK_CLASS_API ReconstructionWriterService : public ::io::IWriter
{

public :
    ~ReconstructionWriterService() throw() {}

    fwCoreServiceClassDefinitionsMacro ( (ReconstructionWriterService)( ::io::IWriter) ) ;

    /**
     * @brief Configure the obj mesh path.
     *
     * This method is used to find
     * the file path  using a file selector.
     */
    IOVTK_API virtual void configureWithIHM();

protected:

    IOVTK_API virtual ::io::IOPathType getIOPathType() const;


    /**
    * @brief Starting method.
    *
    * This method is used to initialize the service.
    */
    IOVTK_API virtual void starting() throw(::fwTools::Failed);

    /**
     * @brief Stopping method.
     *
     * The stopping method is empty for this service.
     */
    IOVTK_API virtual void stopping() throw(::fwTools::Failed);

    /**
     * @brief Updating method.
     *
     * This method is used to update the service.
     * The image is read.
     */
    IOVTK_API void updating() throw(::fwTools::Failed);

    /**
     * @brief React on modifications : default does nothing.
     *
     * @note This method is automatically called by update( msg ) method from base service ( ::fwServices::IService ).
     *
     * @param[in] _msg information message for modification
     */
    void receiving( CSPTR(::fwServices::ObjectMsg) _msg ) throw(::fwTools::Failed){};

    /**
     * @brief Info method.
     *
     * This method is used to give
     * informations about the service.
     */
    IOVTK_API void info(std::ostream &_sstream ) ;


private :

    /**
    * @brief Save a obj mesh.
    * @param[in] _objFile \b const ::boost::filesystem::path.
    * @param[out] _pAcquisition ::boost::shared_ptr< ::fwData::Acquisition >.
    *
    * This method is used to save a reconstruction using the file path.
    */
    void saveReconstruction( const ::boost::filesystem::path _objFile, ::boost::shared_ptr< ::fwData::Acquisition > _pAcquisition );

    /**
    * @brief the m_bServiceIsConfigured value is \b true
    * if the obj mesh path is known.
    */
    bool m_bServiceIsConfigured;

    /**
    * @brief Obj mesh path.
    */
    ::boost::filesystem::path m_fsAcqPath;

};

} // namespace ioVTK

#endif //_IOVTK_RECONSTRUCTIONWRITERSERVICE_HPP_
