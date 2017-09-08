#ifndef VROOM_ZEROMQSERVER_H
#define VROOM_ZEROMQSERVER_H

#include "ExternalProcessCommunicator.h"
#include <rapidjson/document.h>

class ZeroMqServer : public ExternalProcessCommunicator
{
	public:
		virtual ~ZeroMqServer() {};
		virtual void Initialize() override;
		virtual void Destroy() override;
		virtual void BroadcastMessage(const rapidjson::Document& message) override;

	private:
};

#endif