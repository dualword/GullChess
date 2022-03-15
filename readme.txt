Gull 1.2

Features:
    -"movetime" option

Algorithms:
    -significantly improved evaluation
    -refined search
    -several minor bugfixes

Code: still less than 6000 lines!

Gull 1.1

Features:
    -"searchmoves" command support
    -"Clear Hash" command support
    -Tunable version with some additional UCI parameters. 
        It's slightly slower than the standart version, so the latter is better for engine vs engine matches.
    -"+-/=/-+ Evaluation" command: force evaluation of the current position (tunable version only)
    
Algorithms:
    -improved mobility evaluation
    -improved outpost evaluation
    -improved pawn structure evaluation
    -tuned prunings
    -quiet moves in the quiescence search
    -improved hashing & IID

Switches:
    -TUNABLE - standart/tunable compile
    -KNS_TESTING - special testing mode with fixed number of nodes per move

Gull 1.0a

Bugfix:
    -UCI handling bug fixed. This bug occured only in "ponder on" games without adjudication.  
  
Gull 1.0

Features:
    -Ponder support
    -MultiPV support
    -"bench 'depth'" command

Algorithms:
    -magic move generation
    -array of attacks
    -aspiration search
    -IID
    -mvv/lva + SEE
    -history heuristic
    -killer heuristic
    -LMR
    -null move pruning
    -history pruning
    -razoring
    -static null move pruning
    -check extension
    -passed pawn push extension
    -good capture (PV) extension
    -singular move extension
    -quiescence delta pruning
    -quiescence checks
    -PV hashing
    
Code:
    Gull is designed to provide maximum (ELO/coding effort) ratio. 
    All the code (less than 5000 lines) is contained in a single file.
    Hence it compiles faster, and switching between versions is easier.

    Some features (like ->mul and ->positional_score fields of the GData structure)
    aren't used by the current version but will probably be utilized later.

Switches:
    W32_BUILD - must be on for 32-bit version and off for x64
    GEN_MAGICS - turns on the magic number generator
    CPU_TIMING - the engine calculates nps using CPU time when benching.
                 However I'm not sure whether this feature works properly or not
    EPD_TESTING - allows to run a epd test (with "epd 'file'" command)
                  The file must contain pure FEN strings only (without comments or "bm" tag).
                  The test is useful for performance estimation when tuning search heuristics
    ASPIRATION - turns on the aspiration search heuristic

Contact:
    thinkingalot.chess@gmail.com, Vadim Demichev
    