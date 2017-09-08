#ifndef VROOM_EXTERNALPROCESSCOMMUNICATOR_H
#define VROOM_EXTERNALPROCESSCOMMUNICATOR_H

#include <functional>
#include <string>
#include <vector>

#include <rapidjson/document.h>

class ExternalProcessCommunicator
{
public:
	virtual ~ExternalProcessCommunicator() {};
	virtual void Initialize() = 0;
	virtual void Destroy() = 0;
	virtual void BroadcastMessage(const rapidjson::Document& message) = 0;
	virtual bool IsInitialized() { return this->_isInitialized; }

	virtual void RegisterOnMessageReceived(std::function<bool(const rapidjson::Document&)> isMessageForModule, std::function<void(const rapidjson::Document&)> moduleProcessingFunction)
	{
		this->_listeners.push_back(std::pair<std::function<bool(const rapidjson::Document&)>, std::function<void(const rapidjson::Document&)>>(isMessageForModule, moduleProcessingFunction));
	}

	virtual void NotifyListeners(const rapidjson::Document& message)
	{
		for (auto it = this->_listeners.begin(); it != this->_listeners.end(); ++it)
		{
			if (it->first(message))
			{
				it->second(message);
			}
		}
	}

protected:
	bool _isInitialized;
	std::vector<std::pair<std::function<bool(const rapidjson::Document&)>, std::function<void(const rapidjson::Document &)> > > _listeners;
};


#endif