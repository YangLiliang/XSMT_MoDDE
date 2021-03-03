void GetCrossover(int cur) {//Greedy strategy, select the optimal solution
	if (pop[cur].fit_value > pop_tmp.fit_value) {
		for (int i = 1; i <= 3 * (vertice - 1); i++) {
			pop[cur].edge[i] = pop_tmp.edge[i];
		}
	}
}