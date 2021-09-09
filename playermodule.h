#ifndef PLAYERMODULE_H
#define PLAYERMODULE_H

#include "module.h"
#include <boost/asio/deadline_timer.hpp>
#include <boost/bind/bind.hpp>
#include "net/player_controller.h"
#include "map.h"
#include "net/server.h"
#include "debug_tools/out.h"
#include <memory>
#include <vector>

class PlayerModule : public Module
{
    std::vector<std::shared_ptr<player_controller>> players; ///< контролери
    Server host;
    boost::asio::deadline_timer update_timer;
    std::shared_ptr<Map> map;
public:
    PlayerModule(ModuleInterface &interface);

    virtual void Start() override;
private:
    void Update(const boost::system::error_code&);
};

#endif // PLAYERMODULE_H
