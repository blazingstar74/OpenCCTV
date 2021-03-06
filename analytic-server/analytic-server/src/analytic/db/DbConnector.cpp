/*
 * DbConnector.cpp
 *
 *  Created on: Jun 3, 2015
 *      Author: anjana
 */

#include "DbConnector.hpp"

namespace analytic {
namespace db {

sql::Connection* DbConnector::getConnection()
{
	sql::Connection* connPrt = NULL;
	sql::Driver* driverPrt;
	std::string dbUrl, mysqlUsername, mysqlPassword, dbName, mysqlServerName, mysqlPort;
	
	try
	{
		analytic::util::Config* pConfig = analytic::util::Config::getInstance();
		mysqlServerName = pConfig->get(analytic::util::PROPERTY_DB_SERVER_NAME);
		mysqlPort = pConfig->get(analytic::util::PROPERTY_DB_PORT);
		dbName = pConfig->get(analytic::util::PROPERTY_DB_NAME);
		mysqlUsername = pConfig->get(analytic::util::PROPERTY_DB_USERNAME);
		mysqlPassword = pConfig->get(analytic::util::PROPERTY_DB_PASSWORD);

		dbUrl.append("tcp://");
		dbUrl.append(mysqlServerName);
		dbUrl.append(":");
		dbUrl.append(mysqlPort);

	}catch(opencctv::Exception &e)
	{
		std::string sErrorMsg = "DbConnector::getConnection : ";
		throw opencctv::Exception(sErrorMsg.append(e.what()));
	}

	try
	{
		driverPrt = get_driver_instance();
		connPrt = (*driverPrt).connect(dbUrl, mysqlUsername, mysqlPassword);
		(*connPrt).setSchema(dbName);
	}
	catch(sql::SQLException &e)
	{
		//std::cerr << "DbConnector:getConnection: Error while creating connection to the database. " << e.what() << std::endl;
		std::string sErrorMsg = "DbConnector::getConnection : ";
		throw opencctv::Exception(sErrorMsg.append(e.what()));
	}
	return connPrt;
}

} /* namespace db */
} /* namespace analytic */
