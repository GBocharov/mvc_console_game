//
// Created by gleb on 1/28/21.
//

#include "Loggable.h"

void Loggable::SetLogger(const std::shared_ptr<ILogger> &delegate) {
    logger_ = delegate;
}
