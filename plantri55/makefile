CC=gcc
CFLAGS= 
LDFLAGS=
VERSION=55
MY_DIRECTORY=my_work
HAMILTON=contains_hamilton
CLIQUE=contains_clique

all: plantri fullgen

tools: plantri_nft plantri_adj4 plantri_maxd plantri_mdcount plantri_ad \
       plantri_deg plantri_fo pccat

plantri_my: plantri_contains_clique_n plantri_contains_clique_n2 plantri_contains_clique_n4 \
	plantri_is_eulerian plantri_not_simple plantri_contains_hamilton plantri_contains_hamilton_not_checking \
        plantri_contains_hamilton_UF_5 plantri_only_mirror_symetries plantri_no_symetry

plantri: plantri.c
	${CC} -o plantri ${CFLAGS} plantri.c ${LDFLAGS}

plantri_plantri: plantri.c
	${CC} -o ./bin/plantri ${CFLAGS} plantri.c ${LDFLAGS}

plantri_s: plantri.c
	${CC} -o plantri_s ${CFLAGS} -DSPLITTEST plantri.c ${LDFLAGS}

plantri_r: plantri.c
	${CC} -o plantri_r ${CFLAGS} -DSTATS plantri.c ${LDFLAGS}

plantri_nft: plantri.c nft.c
	${CC} -o plantri_nft ${CFLAGS} '-DPLUGIN="nft.c"' plantri.c ${LDFLAGS}

plantri_adj4: plantri.c adj4.c
	${CC} -o plantri_adj4 ${CFLAGS} '-DPLUGIN="adj4.c"' \
		plantri.c ${LDFLAGS}

plantri_maxd: plantri.c maxdeg.c
	${CC} -o plantri_maxd ${CFLAGS} '-DPLUGIN="maxdeg.c"' \
		plantri.c ${LDFLAGS}

plantri_mdcount: plantri.c mdcount.c
	${CC} -o plantri_mdcount ${CFLAGS} '-DPLUGIN="mdcount.c"' \
		plantri.c ${LDFLAGS}

plantri_ad: plantri.c allowed_deg.c
	${CC} -o plantri_ad ${CFLAGS} '-DPLUGIN="allowed_deg.c"' \
		plantri.c ${LDFLAGS}

plantri_deg: plantri.c degseq.c
	${CC} -o plantri_deg ${CFLAGS} '-DPLUGIN="degseq.c"' \
		plantri.c ${LDFLAGS}

plantri_fo: plantri.c faceorbits.c
	${CC} -o plantri_fo ${CFLAGS} '-DPLUGIN="faceorbits.c"' \
		plantri.c ${LDFLAGS}

plantri_min5: plantri.c
	echo "plantri_min5 is obsolete.  Use plantri -m5."

plantri_speed_test: plantri.c ./${MY_DIRECTORY}/speed_test.c
	${CC} -o ./bin/speed_test ${CFLAGS} '-DPLUGIN="./${MY_DIRECTORY}/speed_test.c"' \
		plantri.c ${LDFLAGS}

plantri_is_eulerian: plantri.c ./${MY_DIRECTORY}/is_eulerian.c
	${CC} -o ./bin/is_eulerian ${CFLAGS} '-DPLUGIN="./${MY_DIRECTORY}/is_eulerian.c"' \
		plantri.c ${LDFLAGS}

plantri_contains_clique_n4: plantri.c ./${MY_DIRECTORY}/${CLIQUE}/contains_clique_n4.c
	${CC} -o ./bin/contains_clique_n4 ${CFLAGS} '-DPLUGIN="./${MY_DIRECTORY}/${CLIQUE}/contains_clique_n4.c"' \
		plantri.c ${LDFLAGS}

plantri_contains_clique_n2: plantri.c ./${MY_DIRECTORY}/${CLIQUE}/contains_clique_n2.c
	${CC} -o ./bin/contains_clique_n2 ${CFLAGS} '-DPLUGIN="./${MY_DIRECTORY}/${CLIQUE}/contains_clique_n2.c"' \
		plantri.c ${LDFLAGS}

plantri_contains_clique_n: plantri.c ./${MY_DIRECTORY}/${CLIQUE}/contains_clique_n.c
	${CC} -o ./bin/contains_clique_n ${CFLAGS} '-DPLUGIN="./${MY_DIRECTORY}/${CLIQUE}/contains_clique_n.c"' \
		plantri.c ${LDFLAGS}

plantri_contains_clique_n_wa: plantri.c ./${MY_DIRECTORY}/${CLIQUE}/contains_clique_n_wa.c
	${CC} -o ./bin/contains_clique_n_wa ${CFLAGS} '-DPLUGIN="./${MY_DIRECTORY}/${CLIQUE}/contains_clique_n_wa.c"' \
		plantri.c ${LDFLAGS}

plantri_not_simple: plantri.c ./${MY_DIRECTORY}/not_simple.c
	${CC} -o ./bin/not_simple ${CFLAGS} '-DPLUGIN="./${MY_DIRECTORY}/not_simple.c"' \
		plantri.c ${LDFLAGS}

plantri_not_simple_standard: plantri.c ./${MY_DIRECTORY}/not_simple_standard.c
	${CC} -o ./bin/not_simple_standard ${CFLAGS} '-DPLUGIN="./${MY_DIRECTORY}/not_simple_standard.c"' \
		plantri.c ${LDFLAGS}

plantri_self_edge: plantri.c ./${MY_DIRECTORY}/self_edge.c
	${CC} -o ./bin/self_edge ${CFLAGS} '-DPLUGIN="./${MY_DIRECTORY}/self_edge.c"' \
		plantri.c ${LDFLAGS}

plantri_contains_hamilton: plantri.c ./${MY_DIRECTORY}/${HAMILTON}/contains_hamilton.c
	${CC} -o ./bin/contains_hamilton ${CFLAGS} '-DPLUGIN="./${MY_DIRECTORY}/${HAMILTON}/contains_hamilton.c"' \
		plantri.c ${LDFLAGS}

plantri_contains_hamilton_not_checking: plantri.c ./${MY_DIRECTORY}/${HAMILTON}/contains_hamilton_not_checking.c
	${CC} -o ./bin/contains_hamilton_not_checking ${CFLAGS} '-DPLUGIN="./${MY_DIRECTORY}/${HAMILTON}/contains_hamilton_not_checking.c"' \
		plantri.c ${LDFLAGS}

plantri_contains_hamilton_ultra_checking: plantri.c ./${MY_DIRECTORY}/${HAMILTON}/contains_hamilton_ultra_checking.c
	${CC} -o ./bin/contains_hamilton_ultra_checking ${CFLAGS} '-DPLUGIN="./${MY_DIRECTORY}/${HAMILTON}/contains_hamilton_ultra_checking.c"' \
		plantri.c ${LDFLAGS}

plantri_contains_hamilton_UF_1: plantri.c ./${MY_DIRECTORY}/${HAMILTON}/contains_hamilton_UF_1.c
	${CC} -o ./bin/contains_hamilton_UF_1 ${CFLAGS} '-DPLUGIN="./${MY_DIRECTORY}/${HAMILTON}/contains_hamilton_UF_1.c"' \
		plantri.c ${LDFLAGS}

plantri_contains_hamilton_UF_2: plantri.c ./${MY_DIRECTORY}/${HAMILTON}/contains_hamilton_UF_2.c
	${CC} -o ./bin/contains_hamilton_UF_2 ${CFLAGS} '-DPLUGIN="./${MY_DIRECTORY}/${HAMILTON}/contains_hamilton_UF_2.c"' \
		plantri.c ${LDFLAGS}

plantri_contains_hamilton_UF_3: plantri.c ./${MY_DIRECTORY}/${HAMILTON}/contains_hamilton_UF_3.c
	${CC} -o ./bin/contains_hamilton_UF_3 ${CFLAGS} '-DPLUGIN="./${MY_DIRECTORY}/${HAMILTON}/contains_hamilton_UF_3.c"' \
		plantri.c ${LDFLAGS}

plantri_contains_hamilton_UF_4: plantri.c ./${MY_DIRECTORY}/${HAMILTON}/contains_hamilton_UF_4.c
	${CC} -o ./bin/contains_hamilton_UF_4 ${CFLAGS} '-DPLUGIN="./${MY_DIRECTORY}/${HAMILTON}/contains_hamilton_UF_4.c"' \
		plantri.c ${LDFLAGS}

plantri_contains_hamilton_UF_5: plantri.c ./${MY_DIRECTORY}/${HAMILTON}/contains_hamilton_UF_5.c
	${CC} -o ./bin/contains_hamilton_UF_5 ${CFLAGS} '-DPLUGIN="./${MY_DIRECTORY}/${HAMILTON}/contains_hamilton_UF_5.c"' \
		plantri.c ${LDFLAGS}

plantri_no_symetry: plantri.c ./${MY_DIRECTORY}/no_symetry.c
	${CC} -o ./bin/no_symetry ${CFLAGS} '-DPLUGIN="./${MY_DIRECTORY}/no_symetry.c"' plantri.c ${LDFLAGS}

plantri_only_mirror_symetries: plantri.c ./${MY_DIRECTORY}/only_mirror_symetries.c
	${CC} -o ./bin/only_mirror_symetries ${CFLAGS} '-DPLUGIN="./${MY_DIRECTORY}/only_mirror_symetries.c"' plantri.c ${LDFLAGS}

plantri_scansimple_my: plantri.c ./${MY_DIRECTORY}/scansimple_my.c
	${CC} -o ./bin/scansimple_my ${CFLAGS} '-DPLUGIN="./${MY_DIRECTORY}/scansimple_my.c"' plantri.c ${LDFLAGS} -ggdb3

plantri_operation_b: plantri.c ./${MY_DIRECTORY}/operation_b.c
	${CC} -o ./bin/operation_b ${CFLAGS} '-DPLUGIN="./${MY_DIRECTORY}/operation_b.c"' plantri.c ${LDFLAGS} -ggdb3

plantri_operation_b_without_e3: plantri.c ./${MY_DIRECTORY}/operation_b_without_e3.c
	${CC} -o ./bin/operation_b_without_e3 ${CFLAGS} '-DPLUGIN="./${MY_DIRECTORY}/operation_b_without_e3.c"' plantri.c ${LDFLAGS} -ggdb3

plantri_multiple_e3: plantri.c ./${MY_DIRECTORY}/multiple_e3.c
	${CC} -o ./bin/multiple_e3 ${CFLAGS} '-DPLUGIN="./${MY_DIRECTORY}/multiple_e3.c"' plantri.c ${LDFLAGS} -ggdb3

plantri_multiple_e3_with_e4: plantri.c ./${MY_DIRECTORY}/multiple_e3_with_e4.c
	${CC} -o ./bin/multiple_e3_with_e4 ${CFLAGS} '-DPLUGIN="./${MY_DIRECTORY}/multiple_e3_with_e4.c"' plantri.c ${LDFLAGS} -ggdb3

plantri_extend4: plantri.c ./${MY_DIRECTORY}/extend4.c
	${CC} -o ./bin/extend4 ${CFLAGS} '-DPLUGIN="./${MY_DIRECTORY}/extend4.c"' plantri.c ${LDFLAGS} -ggdb3

plantri_multiple_e4: plantri.c ./${MY_DIRECTORY}/multiple_e4.c
	${CC} -o ./bin/multiple_e4 ${CFLAGS} '-DPLUGIN="./${MY_DIRECTORY}/multiple_e4.c"' plantri.c ${LDFLAGS} -ggdb3

plantri_operation_b_with_looking_for_edges: plantri.c ./${MY_DIRECTORY}/operation_b_with_looking_for_edges.c
	${CC} -o ./bin/operation_b_with_looking_for_edges ${CFLAGS} '-DPLUGIN="./${MY_DIRECTORY}/operation_b_with_looking_for_edges.c"' plantri.c ${LDFLAGS} -ggdb3

plantri_max_degree: plantri.c ./${MY_DIRECTORY}/max_degree.c
	${CC} -o ./bin/max_degree ${CFLAGS} '-DPLUGIN="./${MY_DIRECTORY}/max_degree.c"' plantri.c ${LDFLAGS} -ggdb3

GP=gadgets_priority
plantri_${GP}: plantri.c ./${MY_DIRECTORY}/${GP}.c
	${CC} -o ./bin/${GP} ${CFLAGS} '-DPLUGIN="./${MY_DIRECTORY}/${GP}.c"' plantri.c ${LDFLAGS} -ggdb3

GP2=gadgets_priority_v2
plantri_${GP2}: plantri.c ./${MY_DIRECTORY}/${GP2}.c
	${CC} -o ./bin/${GP2} ${CFLAGS} '-DPLUGIN="./${MY_DIRECTORY}/${GP2}.c"' plantri.c ${LDFLAGS} -ggdb3


fullgen: fullgen.c
	${CC} -o fullgen ${CFLAGS} fullgen.c ${LDFLAGS}

pccat: pcfilter.c pccat.c rng.o
	${CC} -o pccat '-DPLUGIN="pccat.c"' pcfilter.c rng.o

plantri-dist:
	mkdir plantri${VERSION}
	cp plantri.c nft.c adj4.c maxdeg.c mdcount.c allowed_deg.c \
	   degseq.c plantri-guide.txt more-counts.txt fullgen.c \
	   faceorbits.c fullgen-guide.txt LICENSE-2.0.txt \
           ${HOME}/nauty/sumlines.c makefile plantri${VERSION}
	tar cvf plantri${VERSION}.tar plantri${VERSION}
	gzip plantri${VERSION}.tar
	rm -R plantri${VERSION}