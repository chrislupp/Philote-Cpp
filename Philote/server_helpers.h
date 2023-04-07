#pragma once

#include <Philote/explicit_server.h>
#include <Philote/implicit_server.h>

namespace philote
{
    /**
     * @brief Runs an explicit analysis server using a defined analysis server
     * class.
     *
     * @param analysis Explicit analysis server class provided by the
     * user/developer.
     */
    void RunServer(ExplicitServer &analysis);

    /**
     * @brief Runs an implicit analysis server using a defined analysis server
     * class.
     *
     * @param analysis Implicit analysis server class provided by the
     * user/developer.
     */
    void RunServer(ImplicitServer &analysis);
}