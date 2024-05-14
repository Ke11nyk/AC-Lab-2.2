#include "pch.h"
#include "..\JohnsonAlgorithm\Edge.h"
#include "..\JohnsonAlgorithm\GenerateFile.h"

TEST(EdgeTest, EdgeTest)
{
	Edge edge(1, 2, 3);

	EXPECT_EQ(edge.from, 1);
	EXPECT_EQ(edge.to, 2);
	EXPECT_EQ(edge.weight, 3);
}

TEST(GenerateFileTest, GenerateFileTest)
{
	EXPECT_EQ(generateFile(), 0);
}