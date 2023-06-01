cmake_minimum_required(VERSION 2.24)
project(TOg_T_O_groepje_18)

set(CMAKE_CXX_STANDARD 14)


set(TOI_Dio TOi/Dio/DFADio.h TOi/Dio/DFADio.cpp TOi/Dio/ENFADio.h TOi/Dio/ENFADio.cpp TOi/Dio/Mystack.h TOi/Dio/MyStack.cpp TOi/Dio/NFADio.h TOi/Dio/NFADio.cpp TOi/Dio/REDio.h TOi/Dio/REDio.cpp TOi/Dio/StateDio.h TOi/Dio/StateDio.cpp TOi/Dio/StateSetDio.h TOi/Dio/StateSetDio.cpp)
set(TOI_Jonathan TOi/Jonathan/SSC_and_TFA/DFAJonathan.h TOi/Jonathan/SSC_and_TFA/DFAJonathan.cpp TOi/Jonathan/SSC_and_TFA/NFAJonathan.h TOi/Jonathan/SSC_and_TFA/NFAJonathan.cpp TOi/Jonathan/SSC_and_TFA/StateJonathan.h TOi/Jonathan/SSC_and_TFA/StateJonathan.cpp TOi/Jonathan/SSC_and_TFA/TransitionJonathan.h TOi/Jonathan/SSC_and_TFA/TransitionJonathan.cpp)
set(TOI_Sinem TOi/Sinem/Productautomaat/SDFA.cpp TOi/Sinem/Productautomaat/SDFA.h TOi/Sinem/Productautomaat/DFAConfig.cpp TOi/Sinem/Productautomaat/DFAConfig.h TOi/Sinem/TATOi/SNFA.h TOi/Sinem/TATOi/SNFA.cpp TOi/Sinem/TATOi/NFAConfig.h TOi/Sinem/TATOi/NFAConfig.cpp TOi/Sinem/TATOi/State.h TOi/Sinem/TATOi/State.cpp TOi/Sinem/TATOi/ToDFAConfig.h TOi/Sinem/TATOi/ToDFAConfig.cpp TOi/Sinem/TATOi/Transition.h TOi/Sinem/TATOi/Transition.cpp)
set(TOI_Olivia TOi/Olivia/ODFA.cpp TOi/Olivia/ODFA.h TOi/Olivia/ONFA.cpp TOi/Olivia/ONFA.h TOi/Olivia/ORE.cpp TOi/Olivia/ORE.cpp)
set(TOg SpamFilter.cpp SpamFilter.h Utils/SpamFilterUtils.cpp Utils/SpamFilterUtils.h Database.cpp Input.cpp Utils/DBC.h Output.cpp Output.h Utils/DatabaseUtils.cpp Utils/DatabaseUtils.h)



add_executable(TOg_T_O_groepje_18 main.cpp ${TOg} ${TOI_Dio} ${TOI_Jonathan} ${TOI_Sinem} ${TOI_Olivia})
