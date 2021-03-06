/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2012.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef _IOVTK_MESHWRITERSERVICE_HPP_
#define _IOVTK_MESHWRITERSERVICE_HPP_

#include <boost/filesystem/path.hpp>

#include <io/IWriter.hpp>

#include "ioVTK/export.hpp"

namespace fwData
{
    class Mesh;
}

namespace fwServices
{
    class ObjectMsg;
}

namespace ioVTK
{

/**
 * @brief   VTK mesh writer service.
 * @class   MeshWriterService
 *
 * Service writing a VTK Mesh using the fwVtkIO lib.
 *
 * Service registered details : \n
 * fwServicesRegisterMacro( ::io::IWriter , ::ioVTK::MeshWriterService , ::fwData::Mesh )
 */
class IOVTK_CLASS_API MeshWriterService : public ::io::IWriter
{

public :
    ~MeshWriterService() throw() {}

    fwCoreServiceClassDefinitionsMacro ( (MeshWriterService)( ::io::IWriter) ) ;

    /**
    * @brief Configure the mesh path.
    *
    * This method is used to find
    * the file path  using a file selector.
    */
    IOVTK_API virtual void configureWithIHM();

    /**
     * @brief Save a VTK mesh.
     * @param[in] meshFile \b const ::boost::filesystem::path.
     * @param[out] mesh ::boost::shared_ptr< ::fwData::Mesh >.
     *
     * This method is used to save a mesh using the file path.
     */
    IOVTK_API static void saveMesh( const ::boost::filesystem::path& meshFile, const SPTR(::fwData::Mesh)& mesh );



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
    * The mesh is read.
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
    * @brief the m_bServiceIsConfigured value is \b true
    * if the image path is known.
    */
    bool m_bServiceIsConfigured;

    /**
    * @brief Mesh path .
    */
    ::boost::filesystem::path m_fsMeshPath;

};

} // namespace ioVTK

#endif //_IOVTK_MESHWRITERSERVICE_HPP_

