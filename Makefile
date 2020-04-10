test:
	black . --check
	isort -y --check-only --skip esp32ino
	env PYTHONPATH=. pytest --pylint --flake8 --ignore=esp32ino --cov=tests

format:
	black . --exclude esp32ino
	isort -y --skip esp32ino

dev:
	pip install -r requirements.txt
	pip install -r requirements-dev.txt
	pre-commit install
