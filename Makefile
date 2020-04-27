format-py:
	black . --exclude 2w_car
	isort -y --skip 2w_car

format-cpp:
	cpplint ./2w_car/*

format:
	make format-py
	make format-cpp

test-py:
	black . --check
	isort -y --check-only --skip 2w_car
	env PYTHONPATH=. pytest --pylint --flake8 --ignore=2w_car

test-cpp:
	cpplint ./2w_car/*

test:
	make test-py
	make test-cpp

dev:
	pip install -r requirements-dev.txt
	pre-commit install

pypkg:
	pip install -r requirements.txt

