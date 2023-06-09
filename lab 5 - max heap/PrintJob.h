#ifndef __PRINTJOB_H
#define __PRINTJOB_H

class PrintJob {
private:
  int priority;
  int jobNumber;
  int numPages;

public:
  /* creates a new PrintJob with priority,
  jobNumber, and numPages. */
  PrintJob(int, int, int);

  /* returns the priority of the 
  current printJob */
  int getPriority() const;

  /* returns the value of the 
  current jobNumber */
  int getJobNumber() const;

  /* returns the value of the 
  current numPages */
  int getPages() const;

  /* swaps the priority, jobNumber, 
  and numPages of two PrintJobs*/
  void swap(PrintJob *, PrintJob *);
};

#endif