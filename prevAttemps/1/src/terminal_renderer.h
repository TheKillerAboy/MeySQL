#ifndef MEYSQL_TERMINAL_RENDERER_H
#define MEYSQL_TERMINAL_RENDERER_H

#include "table.h"
#include "columntypes.h"

namespace MeySQL{
    class TerminalRenderer{
    public:
        static void renderTable(const MeySQL::Table& table, bool header=true);
    };
}

#endif