/*
 *
 * Copyright 2016, Google Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#include "internal.h"
#include "cgrpc.h"

#include <stdio.h>

grpc_event cgrpc_completion_queue_get_next_event(grpc_completion_queue *cq, double timeout) {
  gpr_timespec deadline = cgrpc_deadline_in_seconds_from_now(timeout);
  if (timeout < 0) {
    deadline = gpr_inf_future(GPR_CLOCK_REALTIME);
  }
  return grpc_completion_queue_next(cq, deadline, NULL);
}

void cgrpc_completion_queue_drain(grpc_completion_queue *cq) {
  grpc_event ev;
  do {
    ev = grpc_completion_queue_next(cq, cgrpc_deadline_in_seconds_from_now(5), NULL);
  } while (ev.type != GRPC_QUEUE_SHUTDOWN);
}

void cgrpc_completion_queue_shutdown(cgrpc_completion_queue *cq) {
  grpc_completion_queue_shutdown(cq);
}

