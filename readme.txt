Gull 2.1 @ 17.06.2013
	Evaluation weights are optimized with the use of automated tuning (source code included). 
	Gull's evaluation is no longer almost identical to that of Ivanhoe. 
	Minor search & time management & SMP efficiency enhancements.

	On SMP & Hyper-Threading:
		By default Gull limits the number of processes to the number of phisical CPU cores availible.
		This is done in order to avoid ELO drop due to significant SMP search overhead at bullet time controls. 
		However for long games & analysis it is recommended to turn HT on and manually set the number of processes (UCI option "Threads")  
		to equal the number of logical CPUs.

	On the automated tuning (technical):
		Tuning is done in two steps:
		1. an estimate of the gradient is calculated;
		2. line search is performed.
	 	SPSA (just move a bit along the gradient direction instead of performing a line search) may also be quite effective, 
		though it's difficult to pick good parameters.
		Fairly simple exit criteria are used for the line search. I don't employ SPRT because it's guaranteed to be optimal only for 
		elo=elo1 vs elo=elo0 hypothesis, whereas in this case we are interested in elo>elo0 vs elo<=elo0 test. However it's still possible
		for SPRT (or some other test) to be better for some elo-elo0 values. Shouldn't be very difficult to run a numerical comparision
		between various tests.	  

Gull II @ 20.12.2012
	Slightly modified eval & search. 
	Significantly improved parallel search efficiency at long time controls.   

Gull II beta2 @ 17.07.2012
	Compatibility with XP finally fixed. +Knight underpromotion bug fixed. 
	The change in playing strength should be negligible.

Gull II beta xp @ 17.07.2012
	Compatibility with Windows XP fixed. No need for update if you use Vista/7/8.
	Still Gull will not run under any Windows older than XP.

Gull II beta @ 16.07.2012
	A derivative of Gull 1.2 (program structure, board representation, move generators etc.) & Ivanhoe (versions 63 & 46: evaluation). 
	Whether future versions will retain Ivanhoe's evaluation is still undecided. 

	Gull II beta supports multi-core CPUs. For now parallel algorithms are pretty basic, and performance gain isn't very good. 
	P.S. Gull employs processes instead of threads for the sake of code simplicity.

	P.P.S. This version may be buggy (tested only on my home PC). That's why it is a beta :) 
