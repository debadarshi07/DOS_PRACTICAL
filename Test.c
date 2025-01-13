/* program producerconsumer */
int n;
binary_semaphore s = 1, delay = 0;
void producer() {
    while (true) {
        produce();
        semWaitB(s);
        append();
        n++;
        if (n == 1)
            semSignalB(delay);
        semSignalB(s);
    }
}
void consumer() {
    semWaitB(delay);
    while (true) {
        semWaitB(s);
        take();
        n--;
        semSignalB(s);
        consume();
        if (n == 0)
            semWaitB(delay);
    }
}
void main() {
    n = 0;
    parbegin(producer, consumer);
}