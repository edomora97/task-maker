#ifndef WORKER_EXECUTOR_HPP
#define WORKER_EXECUTOR_HPP

#include <mutex>

#include "capnp/evaluation.capnp.h"
#include "sandbox/sandbox.hpp"
#include "util/file.hpp"
#include "worker/manager.hpp"

namespace worker {

class Executor : public capnproto::Evaluator::Server {
 public:
  KJ_DISALLOW_COPY(Executor);
  Executor(capnproto::FileSender::Client server, Manager& manager)
      : server_(server), manager_(manager) {}

  kj::Promise<void> evaluate(EvaluateContext context) {
    auto request = context.getParams().getRequest();
    return Execute(request, context.getResults().initResult());
  }

  kj::Promise<void> requestFile(RequestFileContext context) {
    return util::File::HandleRequestFile(context);
  }

 private:
  kj::Promise<void> Execute(capnproto::Request::Reader request,
                            capnproto::Result::Builder result);

  static const constexpr char* kBoxDir = "box";

  capnproto::FileSender::Client server_;
  Manager& manager_;
};

}  // namespace worker

#endif
