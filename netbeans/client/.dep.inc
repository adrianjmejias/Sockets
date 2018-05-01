# This code depends on make tool being used
include ${DEPFILES}
endif
DEPFILES=$(wildcard $(addsuffix .d, ${OBJECTFILES} ${TESTOBJECTFILES}))
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
