#include "worker/main.hpp"
#include <capnp/ez-rpc.h>
#include <thread>

#include "capnp/server.capnp.h"
#include "util/daemon.hpp"
#include "util/flags.hpp"
#include "util/misc.hpp"
#include "util/version.hpp"
#include "worker/executor.hpp"
#include "worker/manager.hpp"

namespace worker {
kj::MainBuilder::Validity Main::Run() {
  if (Flags::daemon) {
    util::daemonize(Flags::pidfile);
  }
  if (Flags::server == "") {
    return "You need to specify a server!";
  }
  Manager manager(Flags::server, Flags::port, Flags::num_cores,
                  Flags::pending_requests, Flags::name);
  manager.Run();
  return true;
}

kj::MainFunc Main::getMain() {
  return kj::MainBuilder(context, "Task-Maker Worker (" + util::version + ")",
                         "Executes requests pulled from a server")
      .addOption({'k', "keep_sandboxes"}, util::setBool(Flags::keep_sandboxes),
                 "Keep the sandboxes after evaluation")
      .addOptionWithArg({'n', "num-cores"}, util::setInt(Flags::num_cores),
                        "<N>", "Number of cores to use")
      .addOptionWithArg({'s', "server"}, util::setString(Flags::server),
                        "<ADDRESS>", "Address to connect to")
      .addOptionWithArg({'p', "port"}, util::setInt(Flags::port), "<PORT>",
                        "Port to connect to")
      .addOptionWithArg({"name"}, util::setString(Flags::name), "<NAME>",
                        "Name of this worker")
      .addOptionWithArg({'t', "temp"}, util::setString(Flags::temp_directory),
                        "<TEMP>", "Where to store the sandboxes")
      .addOptionWithArg({'r', "pending-requests"},
                        util::setInt(Flags::pending_requests), "<REQS>",
                        "Maximum number of pending requests")
      .callAfterParsing(KJ_BIND_METHOD(*this, Run))
      .build();
}
}  // namespace worker
