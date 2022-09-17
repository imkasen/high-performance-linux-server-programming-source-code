/* 带状态转移的有限状态机

{
    State cur_State = type_A;
    while (cur_State != type_C) {
        Package_pack = getNewPackage();
        switch (cur_State) {
            case type_A:
                process_package_state_A(_pack);
                cur_State = type_B;
                break;
            case type_B:
                process_package_state_B(_pack);
                cur_State = type_C;
                break;
        }
    }
}

*/
