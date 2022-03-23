#include "pcs/lts/parsers.h"
#include <gtest/gtest.h>

#include <string>
#include <filesystem>

#include "pcs/lts/lts.h"

TEST(ParseLTS, LTS1) {
	pcs::lts::LabelledTransitionSystem got;
	pcs::lts::ReadFromFile(got, "../../tests/lts/testdata/lts_1.txt");

	pcs::lts::LabelledTransitionSystem expected;
	pcs::lts::State s0("s0");
	s0.AddTransistion("a1", "s1");
	expected.AddState(s0);
	expected.SetInitialState("s0", false);

	pcs::lts::State s1("s1");
	s1.AddTransistion("a2", "s2");
	expected.AddState(s1);

	pcs::lts::State s2("s2");
	expected.AddState(s2);

	ASSERT_EQ(got, expected);
}

TEST(ParseJsonLTS, LTS1) {
	pcs::lts::LabelledTransitionSystem got;
	pcs::lts::ReadFromJSONFile(got, "../../tests/lts/testdata/lts_1.json");

	pcs::lts::LabelledTransitionSystem expected;
	pcs::lts::State s0("s0");
	s0.AddTransistion("a1", "s1");
	expected.AddState(s0);
	expected.SetInitialState("s0", false);

	pcs::lts::State s1("s1");
	s1.AddTransistion("a2", "s2");
	expected.AddState(s1);

	pcs::lts::State s2("s2");
	expected.AddState(s2);

	ASSERT_EQ(got, expected);
}