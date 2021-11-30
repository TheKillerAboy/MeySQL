read -r -d '' BUMP_VERSION_PY << EOM
from setup import *
config = load_config()
bump_version(config)
save_config(config)
EOM

python -c "$BUMP_VERSION_PY"
python setup.py sdist