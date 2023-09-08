<h1>Producer-consumer problem with unlimited buffer</h1>
<p>
  The producer-consumer problem is a synchronization problem in which one or multiple producers generate data, and one or multiple consumers consume this data. To solve this problem using an unlimited buffer in C++, you can use Semaphores and Threads.
</p>
<p>
  The output buffer is a two-way queue used as a synchronization resource. The producers add data to the queue, and the consumers remove data from the queue. If the queue is full, the producer must wait for the consumer to remove data, and vice versa.
</p>
<p>
  The producer function in this program is created to generate numbers. It uses a loop to produce BUFFER_SIZE numbers consecutively and uses unique_lock for resource synchronization. If the buffer is full, the producer must wait for the consumer to remove items from it to make space for new production. In this case, the producer stops itself by calling produce_cv.wait(lck) on its own condition variable. When there is enough space to add an item to the queue, the producer adds a new number to the queue and doesn't wait for the consumer to consume it by using consume_cv.notify_one().
</p>
<p>
  The consumer function is created to read numbers from the produced queue. Similar to the producer, this function uses a loop to read BUFFER_SIZE numbers from the queue and uses unique_lock for resource synchronization. If the buffer is empty (meaning there are no items in it), the consumer must wait for the producer to add new items to the queue. In this case, the consumer stops itself by calling consume_cv.wait(lck) on its condition variable. When an item is available for consumption, the consumer removes it from the queue and doesn't wait for the producer to produce more items by using produce_cv.notify_one().
</p>
<p>
  In the end, three threads for production and consumption are created. By calling join() for all of them, the program will wait until all threads are finished.
</p>
