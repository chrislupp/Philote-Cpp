/*
    Philote C++ Bindings

    Copyright 2022-2024 Christopher A. Lupp

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.

    This work has been cleared for public release, distribution unlimited, case
    number: AFRL-2023-5716.

    The views expressed are those of the authors and do not reflect the
    official guidance or position of the United States Government, the
    Department of Defense or of the United States Air Force.

    Statement from DoD: The Appearance of external hyperlinks does not
    constitute endorsement by the United States Department of Defense (DoD) of
    the linked websites, of the information, products, or services contained
    therein. The DoD does not exercise any editorial, security, or other
    control over the information you may find at these locations.
*/
#include <gtest/gtest.h>

#include <discipline.h>
#include <disciplines_mock.grpc.pb.h>

using philote::DisciplineServer;
using philote::Discipline;

/*
	Test the link and unlink pointers functions.
*/
TEST(DisciplineServerTests, LinkPointers)
{
	Discipline disc;
	DisciplineServer server;

	EXPECT_TRUE(server.DisiplinePointerNull());

	server.LinkPointers(&disc);
	EXPECT_FALSE(server.DisiplinePointerNull());

	server.UnlinkPointers();
	EXPECT_TRUE(server.DisiplinePointerNull());

}

/*
	Test the get info function.
*/
TEST(DisciplineServerTests, GetInfo)
{
	Discipline disc;
	DisciplineServer server;

	server.LinkPointers(&disc);

	server.UnlinkPointers();
}

/*
	Test the set stream options function.
*/
TEST(DisciplineServerTests, SetStreamOptions)
{
	Discipline disc;
	DisciplineServer server;

	server.LinkPointers(&disc);

	server.UnlinkPointers();
}

/*
	Test the set options function.
*/
TEST(DisciplineServerTests, SetOptions)
{
	Discipline disc;
	DisciplineServer server;

	server.LinkPointers(&disc);

	server.UnlinkPointers();
}

/*
	Test the get variable definitions function.
*/
TEST(DisciplineServerTests, GetVariableDefinitions)
{
	Discipline disc;
	DisciplineServer server;

	server.LinkPointers(&disc);

	server.UnlinkPointers();
}

/*
	Test the get partial definitions function.
*/
TEST(DisciplineServerTests, GetPartialDefinitions)
{
	Discipline disc;
	DisciplineServer server;

	server.LinkPointers(&disc);

	server.UnlinkPointers();
}

/*
	Test the setup function.
*/
TEST(DisciplineServerTests, Setup)
{
	Discipline disc;
	DisciplineServer server;

	server.LinkPointers(&disc);

	server.UnlinkPointers();
}