#include <stdio.h>
#include <stdlib.h>

#define max_student_count (int)50
#define subject_count (int)5

typedef struct student_
{
	int code, score[subject_count];
	double total;
} Student;

typedef struct rank_
{
	int code, rank;
} Rank;

Student Students[max_student_count];
Rank Ranks[max_student_count];

int Priority[subject_count], N;
double Weight[subject_count];

void CalcAndWriteRanks()
{
	for (int i = 0; i < N; i++)
	{
		double total = 0;
		for (int j = 0; j < subject_count; j++)
			total += (double)Students[i].score[j] * Weight[j];
		Students[i].total = total;
	}

	for (int i = 0; i < N; i++)
	{
		int rank = 1;
		for (int j = 0; j < N; j++)
		{
			if (Students[i].total < Students[j].total)
				rank++;
			else if (Students[i].total == Students[j].total)
			{
				// 哇, 好屎啊, 好在过了
				for (int k = 0; k < subject_count; k++)
				{
					const int
						p = Students[i].score[Priority[k] - 1],
						q = Students[j].score[Priority[k] - 1];

					if (p == q)
						continue;

					if (p < q)
						rank++;
					break;
				}
			}
		}
		Ranks[i].rank = rank;
		Ranks[i].code = Students[i].code;
	}

}

// Review the if-null target
void PrintRanks()
{
	for (int i = 0; i < N; i++)
		printf("%d %d\n", Ranks[i].rank, Ranks[i].code);
}

int comparePairs(const void *a, const void *b)
{
	const Rank *pairA = (Rank*) a, *pairB = (Rank*) b;

    if (pairA -> rank != pairB -> rank)
        return pairA -> rank - pairB -> rank;
    return pairA -> code - pairB -> code;
}

int main(void)
{
	// N is the number of students
	scanf("%d", &N); // NOLINT(*-err34-c)

	// This is the priority of each subject
	for (int i = 0; i < subject_count; i++)
		scanf("%d", Priority + i); // NOLINT(*-err34-c)

	// This is the weight of each subject
	for (int i = 0; i < subject_count; i++)
		scanf("%lf", Weight + i); // NOLINT(*-err34-c)
	
	// This is the information of each student
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &Students[i].code); // NOLINT(*-err34-c)
		for (int j = 0; j < subject_count; j++)
			scanf("%d", Students[i].score + j); // NOLINT(*-err34-c)
	}

	CalcAndWriteRanks();
	qsort(Ranks, N, sizeof(Rank), comparePairs);

	PrintRanks();
	return 0;
}