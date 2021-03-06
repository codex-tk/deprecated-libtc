#include "stdafx.h"
#include "factory.hpp"

namespace tc {
namespace log {


factory& factory::instance(void){
	static factory ins;
	return ins;
}

factory::factory( void ){

}

factory::~factory( void ) {
}

std::shared_ptr<tc::log::encoder> factory::create_encoder( const std::string& name
		, const std::string& param ) 
{
	auto it = _encoders.find(name);
	if ( it != _encoders.end() ) {
		return it->second( param );
	}
	return std::shared_ptr<tc::log::encoder>(nullptr);
}

std::shared_ptr<tc::log::writer> factory::create_writer( const std::string& name
		, const std::string& param ) 
{
	auto it = _writers.find(name);
	if ( it != _writers.end() ) {
		return it->second( param );
	}
	return std::shared_ptr<tc::log::writer>(nullptr);
}
void factory::register_encoder( const std::string& name 
		, const tc::function< std::shared_ptr<tc::log::encoder>  ( const std::string& param ) >& encoder_create )
{
	_encoders[name] = encoder_create;
}
void factory::register_writer( const std::string& name 
		, const tc::function< std::shared_ptr<tc::log::writer> ( const std::string& param ) >& write_create )
{
	_writers[name] = write_create;
}


}}
