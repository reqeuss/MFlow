# MFlow Architecture

MFlow models media processing as an explicit execution pipeline rather than one opaque operation.

## Current layers

- **Core:** pipeline, scheduler, memory ownership and system information.
- **Media:** lightweight probing today; stream/packet/frame abstractions will follow.
- **Backends:** planned FFmpeg/libav and hardware backends.
- **CLI:** intentionally thin; processing logic stays in the core.

## Target graph

```text
Source
  |
  v
Demux
  |
  v
Stream Planner
  +-------------------+
  |                   |
 Video               Audio
  |                   |
 Decode              Decode
  |                   |
  +--------+----------+
           |
      Filter Graph
           |
      Memory Planner
           |
         Encode
           |
          Mux
           |
         Sink
```

## Optimization principles

1. Identify what output is actually required.
2. Avoid unnecessary streams and bytes.
3. Reuse buffers when lifetimes permit.
4. Keep data on the same processing device when possible.
5. Fuse compatible operations where safe.
6. Schedule work according to dependencies and available hardware.
7. Measure every optimization with reproducible workloads.

## Future zero-copy path

```text
GPU Decode -> GPU Filter -> GPU Resize -> GPU Encode
```

instead of repeatedly moving frames through system RAM.

MFlow 0.1 is deliberately small: it establishes the architecture before introducing complex codec implementations.
