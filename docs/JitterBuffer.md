# Jitter Buffer Implementation
The design uses three threads: One servicing the incoming fragments, assembling them into complete frames. One decoding the frames. With the final thread servicing the frames to be rendered. 

Having three threads adds complexity and requires synchronisation but does mean each of the three stages can run at their own rate and not at the frequency of the incoming fragments. This is particularly useful when incoming fragments are late, allowing the decoder and renderer to continue processing and provide a smoother playback. The queues between each stages provide this buffering but because they cross thread boundaries need to be made thread-safe.

## CLazyBuffer
This implements a simple lazy allocated buffer. The internal buffer will grow to the size of the largest buffer but not shrink. The hope is that over time the require buffer size with stabilize, removing the need to allocate or deallocate chunks of memory inside the main loop
CRenderBuffer
This class is a specialised version of CLazyBuffer which preallocates a one megabyte internal buffer. Because the specification says the render buffer size will always be under one megabyte each buffer should only need to be allocated at the start of day.

The size is clamped between zero and one megabyte in an attempt to avoid buffer overflows. This has the limitation of clipping the buffer to be rendered if the size happens to go over one megabyte but that seems a worthwhile trade off instead of accessing unallocated memory.  

## CFrame
This class tracks the fragments that make up the incoming frame. The fragments are stored in a vector of CLazyBuffers, again the hope is the number of fragments will be fairly constant  over frames, so limiting the amount of reallocation required. 
If multiple copies of the same fragment are passed in the second copy will be dropped. This could leads to a permanently missing fragments and so an incomplete frame, stalling the pipeline.   
Fragments presented after the frame has been completed are also dropped, this should not have a side effects as long as the frame number is correct.
This class also contains the code for timing how long a frame takes to be received. 
The Combine function makes use of the protected functions inside CLazyBuffer to copy into subregions of the outputs internal buffer. They protected to avoid exposing these interface as part of the public API. 
One unimplemented optimization would be not copying the last fragment of a frame into the internal buffer but copying directly into the output buffer, this may not give a noticeable speed-up depending on the size 

## CBufferQueue
This is a simple template class to manage the queues between the pipeline stages. The class used two deque's: one to the buffer that can be reused, with the other holding the buffers ready to be processed by the next stage in the pipeline. They also contain a mutex per deque to control thread safe access. 
The objects are not passed around directly but as pointers, as another way of avoiding copying large  amounts of memory. This does lead to more complex clean up code which is more more prone to memory leaks. 

The number of object allocated is not currently limited, which on a low memory system could be a problem. A future enhancement could limit the number of object created to put an upper bound of the memory usage.

## CJitterBuffer
This class contains the majority of the high level logic and the thread management.

Frames are stored in a stl map when being processed to allow easy look ups of multiple frames based on the frame number. Frames available for reuse are again stored in a deque and like the CBufferQueue pointers are used to avoid reallocating the quite heavyweight CFrame objects. The frame processing also does not have an upper bound on the number of objects, so could also benefit for the same limit as CBufferQueue.

Frames stay in the map even when completed and are only moved the decoder queue in frame number order. As the frame completed frames are moved into the decoders input queue 

The serviceDecoder function is fairly simple, just trying to frames from the input side to the output side for the renderer as fast as they can be decoded.  

ServiceRenderer is nearly as simple as serviceDecoder but sleeps after completing a frame for the mean time taken to receive frame, as a way to try and match the rendering speed to the input frame rate. This is a very simple scheme and would be a good target for future enhancement.
]
## Other Possible Improvements
The interfaces all use int parameters which do not require values less than zero, so could be made into unsigned integers. Also those parameter could have const added to them to provide a little more type safety.

## Time Spent
My initial estimate was the whole project would take 30 hours over the nearly two weeks. In the end the project took nearer 40 hours.
The initial design took around five hours. Creating the unit tests took around two hours. Programming took the bulk of the time at around 20 hours. Testing and debugging took around four hours. Refactoring took up about four hours. With documentation taking around five hours.
