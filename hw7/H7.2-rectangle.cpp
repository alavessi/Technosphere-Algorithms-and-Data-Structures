#include <iostream>
#include <vector>
#include <stack>

int main()
{
    size_t N, M;
    std::cin >> N >> M;
    std::vector<std::vector<bool> > A(N, std::vector<bool>(M));
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < M; j++)
        {
            int value;
            std::cin >> value;
            A[i][j] = value & 1;
        }
    }
    size_t max_rectangle = 0;
    std::vector<int> d(M, -1), d1(M), d2(M);
    std::stack<int> st;
    for (size_t i = 0; i < N; i++)
    {
	    for (size_t j = 0; j < M; j++)
        {
		    if (!A[i][j])
            {
			    d[j] = i;
            }
        }
        while (!st.empty())
        {
            st.pop();
        }
        for (size_t j = 0; j < M; j++)
        {
		    while (!st.empty() && d[st.top()] <= d[j])
            {
                st.pop();
            }
            d1[j] = st.empty() ? -1 : st.top();
		    st.push(j);
	    }
	    while (!st.empty())
        {
            st.pop();
        }
        for (size_t j = M; j > 0; j--)
        {
		    while (!st.empty() && d[st.top()] <= d[j - 1])
            {
                st.pop();
            }
            d2[j - 1] = st.empty() ? M : st.top();
		    st.push(j - 1);
	    }
	    for (size_t j = 0; j < M; j++)
        {
		    max_rectangle = std::max(max_rectangle, (i - d[j]) * (d2[j] - d1[j] - 1));
        }
    }
    std::cout << max_rectangle;
    return 0;
}