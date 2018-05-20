enqueue_heap = importdata('~/Github/Counting_and_Ploting/enqueue_heap');
enqueue_list = importdata('~/Github/Counting_and_Ploting/enqueue_list');
dequeue_heap = importdata('~/Github/Counting_and_Ploting/dequeue_heap');
dequeue_list = importdata('~/Github/Counting_and_Ploting/dequeue_list');

x = 0:1:999;

figure
plot(1000 - x, dequeue_list, '.');
hold on
plot(1000 - x, dequeue_heap, '.');
hold off
title('Binary Heap vs Linked List on dequeue operation');
xlabel('elements enqueued');
ylabel('numbers of comparisons needed');
legend('linked list','binary heap');

figure
plot(x, enqueue_list, '.');
hold on
plot(x, enqueue_heap, '.');
hold off
title('Binary Heap vs Linked List on enqueue operation');
xlabel('elements enqueued');
ylabel('numbers of comparisons needed');
legend('linked list','binary heap');