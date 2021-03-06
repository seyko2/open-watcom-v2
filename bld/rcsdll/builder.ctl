# RCSDLL Builder Control file
# ===========================

set PROJDIR=<CWD>
set PROJNAME=rcsdll

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ INCLUDE <OWROOT>/build/defrule.ctl ]

[ BLOCK <1> rel ]
    cdsay <PROJDIR>

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> wini86/rcsdll.dll   <OWRELROOT>/binw/rcsdll.dll
    <CCCMD> os2386/rcsdll.dll   <OWRELROOT>/binp/dll/rcsdll.dll
    <CCCMD> nt386/rcsdll.dll    <OWRELROOT>/binnt/rcsdll.dll
    <CCCMD> ntaxp/rcsdll.dll    <OWRELROOT>/axpnt/rcsdll.dll
    <CCCMD> ntx64/rcsdll.dll    <OWRELROOT>/binnt64/rcsdll.dll

    <CCCMD> batch/dos386/*.bat  <OWRELROOT>/binw/
    <CCCMD> batch/os2386/*.cmd  <OWRELROOT>/binp/
    <CCCMD> batch/nt386/*.bat   <OWRELROOT>/binnt/
    <CCCMD> batch/ntaxp/*.bat   <OWRELROOT>/axpnt/
    <CCCMD> batch/ntx64/*.bat   <OWRELROOT>/binnt64/

[ BLOCK . . ]
#============
cdsay <PROJDIR>
