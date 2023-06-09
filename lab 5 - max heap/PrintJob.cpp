#include "PrintJob.h"

// priority is the number which the max-heap is going to be sorted
PrintJob::PrintJob(int setP, int setJ, int numP) : 
                                priority(setP),
                                jobNumber(setJ), 
                                numPages(numP) {}

int PrintJob::getPriority() const {
    return priority;
}

int PrintJob::getJobNumber() const {
    return jobNumber;
}

int PrintJob::getPages() const {
    return numPages;
}

void PrintJob::swap(PrintJob *first, PrintJob *second) {
    // int p, j, and n are temporary variables for
    // priority, jobNumber, and numPages, respectively,
    // so we can swap those three values
    int p, j, n;
    p = first->priority;
    j = first->jobNumber;
    n = first->numPages;

    first->priority = second->priority;
    first->jobNumber = second->jobNumber;
    first->numPages = second->numPages;

    second->priority = p;
    second->jobNumber = j;
    second->numPages = n;
}