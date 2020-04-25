format-py:
	black . --exclude esp32ino
	isort -y --skip esp32ino

format-cpp:
	cpplint ./esp32ino/*

format:
	make format-py
	make format-cpp

test-py:
	black . --check
	isort -y --check-only --skip esp32ino
	env PYTHONPATH=. pytest --pylint --flake8 --ignore=esp32ino --cov=tests

test-cpp:
	cpplint ./esp32ino/*

dev:
	pip install -r requirements.txt
	pip install -r requirements-dev.txt
	pre-commit install
