import os
import hashlib
import platform
import subprocess
from subprocess import check_output

import pytest

PROGRAM = './ft_ssl'


# =========== helpers ===========

def _hash(bstring, algo='md5'):
	return getattr(hashlib, algo)(bstring).hexdigest()

def hashstr(string, algo='md5'):
	return _hash(string.encode(), algo)

def hashfile(file, algo='md5'):
	with open(file, 'rb') as f:
		buf = f.readlines()

	return _hash(b''.join(buf), algo)
# ===============================


# =========== MD5 ===========

def test_md5_empty_hash():
	command = [f'{PROGRAM}', 'md5', '-s' , '']
	out = check_output(command).decode()
	expected = 'MD5 ("") = %s\n' % hashstr("")

	assert out == expected

def test_md5_simple_hash():
	command = [f'{PROGRAM}', 'md5', '-s' , 'toto']
	out = check_output(command).decode()
	expected = 'MD5 ("toto") = %s\n' % hashstr("toto")

	assert out == expected

def test_md5_simple_hash_r_arg():
	command = [f'{PROGRAM}', 'md5', '-r', '-s' , 'toto']
	out = check_output(command).decode()
	expected = '%s "toto"\n' % hashstr("toto")

	assert out == expected

def test_md5_simple_hash_q_arg():
	command = [f'{PROGRAM}', 'md5', '-q', '-s' , 'toto']
	out = check_output(command).decode()
	expected = '%s\n' % hashstr("toto")

	assert out == expected

def test_md5_simple_stdin_hash():
	command = [f'{PROGRAM}', 'md5']
	out = check_output(command, input=b'toto').decode()
	expected = '%s\n' % hashstr("toto")

	assert out == expected

def test_md5_simple_stdin_hash_p_arg():
	command = [f'{PROGRAM}', 'md5', '-p']
	out = check_output(command, input=b'toto\n').decode()
	expected = 'toto\n%s\n' % hashstr("toto\n")

	assert out == expected

def test_md5_simple_stdin_hash_multiple_arg():
	command = [f'{PROGRAM}', 'md5', '-q', '-p', '-r']
	out = check_output(command, input=b'toto\n').decode()
	expected = 'toto\n%s\n' % hashstr("toto\n")

	assert out == expected

def test_md5_simple_file_hash():
	command = [f'{PROGRAM}', 'md5', './README.md']
	out = check_output(command).decode()
	expected = 'MD5 (./README.md) = %s\n' % hashfile('./README.md')

	assert out == expected

# subject tests
def test_md5_subject_1():
	command = [f'{PROGRAM}', 'md5']
	out = check_output(command, input=b'pickle rick\n').decode()
	expected = '%s\n' % hashstr("pickle rick\n")

	assert out == expected

def test_md5_subject_2():
	command = [f'{PROGRAM}', 'md5', '-p']
	out = check_output(command, input=b'Do not pity the dead, Harry.\n').decode()
	expected = 'Do not pity the dead, Harry.\n%s\n' % hashstr("Do not pity the dead, Harry.\n")

	assert out == expected

def test_md5_subject_3():
	command = [f'{PROGRAM}', 'md5', '-q', '-r']
	out = check_output(command, input=b'Pity the living.\n').decode()
	expected = '%s\n' % hashstr("Pity the living.\n")

	assert out == expected

def test_md5_subject_4():
	with open('file', 'w+') as tfile:
		tfile.write('And above all,\n')
	command = [f'{PROGRAM}', 'md5', 'file']
	out = check_output(command).decode()
	expected = 'MD5 (file) = %s\n' % hashfile('file')
	os.remove('file')

	assert out == expected

def test_md5_subject_5():
	with open('file', 'w+') as tfile:
		tfile.write('And above all,\n')
	command = [f'{PROGRAM}', 'md5', '-r', 'file']
	out = check_output(command).decode()
	expected = '%s file\n' % hashfile('file')
	os.remove('file')

	assert out == expected

def test_md5_subject_6():
	command = [f'{PROGRAM}', 'md5', '-s', "pity those that aren't following baerista on spotify."]
	out = check_output(command).decode()
	expected = 'MD5 ("pity those that aren\'t following baerista on spotify.") = %s\n' % hashstr(
		'pity those that aren\'t following baerista on spotify.'
	)

	assert out == expected

def test_md5_subject_7():
	with open('file', 'w+') as tfile:
		tfile.write('And above all,\n')
	command = [f'{PROGRAM}', 'md5', '-p', 'file']
	out = check_output(command, input=b'be sure to handle edge cases carefully\n').decode()
	expected = (
		'be sure to handle edge cases carefully\n'
		'{}\nMD5 (file) = {}\n'
	).format(
		hashstr('be sure to handle edge cases carefully\n'),
		hashfile('file'),
	)
	os.remove('file')

	assert out == expected

def test_md5_subject_8():
	with open('file', 'w+') as tfile:
		tfile.write('And above all,\n')
	command = [f'{PROGRAM}', 'md5', 'file']
	out = check_output(command, input=b'some of this will not make sense at first\n').decode()
	expected = (
		'MD5 (file) = {}\n'
	).format(
		hashfile('file'),
	)
	os.remove('file')

	assert out == expected

def test_md5_subject_9():
	with open('file', 'w+') as tfile:
		tfile.write('And above all,\n')
	command = [f'{PROGRAM}', 'md5', '-p', '-r', 'file']
	out = check_output(command, input=b'but eventually you will understand\n').decode()
	expected = (
		'but eventually you will understand\n'
		'{}\n{} file\n'
	).format(
		hashstr('but eventually you will understand\n'),
		hashfile('file'),
	)
	os.remove('file')

	assert out == expected

def test_md5_subject_10():
	with open('file', 'w+') as tfile:
		tfile.write('And above all,\n')
	command = [f'{PROGRAM}', 'md5', '-p', '-s', 'foo', 'file']
	out = check_output(command, input=b'GL HF let\'s go\n').decode()
	expected = (
		'GL HF let\'s go\n'
		'{}\nMD5 ("foo") = {}\nMD5 (file) = {}\n'
	).format(
		hashstr('GL HF let\'s go\n'),
		hashstr('foo'),
		hashfile('file'),
	)
	os.remove('file')

	assert out == expected

def test_md5_subject_11():
	with open('file', 'w+') as tfile:
		tfile.write('And above all,\n')
	command = [f'{PROGRAM}', 'md5', '-r', '-p', '-s', 'foo', 'file', '-s', 'bar']
	out = check_output(command, input=b'one more thing\n', stderr=subprocess.STDOUT).decode()
	expected = (
		'one more thing\n'
		'{}\n{} "foo"\n{} file\n'
		'ft_ssl: md5: -s: No such file or directory\n'
		'ft_ssl: md5: bar: No such file or directory\n'
	).format(
		hashstr('one more thing\n'),
		hashstr('foo'),
		hashfile('file'),
	)
	os.remove('file')

	assert out == expected

def test_md5_subject_12():
	with open('file', 'w+') as tfile:
		tfile.write('And above all,\n')
	command = [f'{PROGRAM}', 'md5', '-r', '-q', '-p', '-s', 'foo', 'file']
	out = check_output(command, input=b'just to be extra clear\n').decode()
	expected = (
		'just to be extra clear\n'
		'{}\n{}\n{}\n'
	).format(
		hashstr('just to be extra clear\n'),
		hashstr('foo'),
		hashfile('file'),
	)
	os.remove('file')

	assert out == expected

# ===============================

# =========== SHA256 ===========

def test_sha256_empty_hash():
	command = [f'{PROGRAM}', 'sha256', '-s' , '']
	out = check_output(command).decode()
	expected = 'SHA256 ("") = %s\n' % hashstr("", algo='sha256')

	assert out == expected

def test_sha256_simple_hash():
	command = [f'{PROGRAM}', 'sha256', '-s' , 'toto']
	out = check_output(command).decode()
	expected = 'SHA256 ("toto") = %s\n' % hashstr("toto", algo='sha256')

	assert out == expected

def test_sha256_simple_hash_r_arg():
	command = [f'{PROGRAM}', 'sha256', '-r', '-s' , 'toto']
	out = check_output(command).decode()
	expected = '%s "toto"\n' % hashstr("toto", algo='sha256')

	assert out == expected

def test_sha256_simple_hash_q_arg():
	command = [f'{PROGRAM}', 'sha256', '-q', '-s' , 'toto']
	out = check_output(command).decode()
	expected = '%s\n' % hashstr("toto", algo='sha256')

	assert out == expected

def test_sha256_simple_stdin_hash():
	command = [f'{PROGRAM}', 'sha256']
	out = check_output(command, input=b'toto').decode()
	expected = '%s\n' % hashstr("toto", algo='sha256')

	assert out == expected

def test_sha256_simple_stdin_hash_p_arg():
	command = [f'{PROGRAM}', 'sha256', '-p']
	out = check_output(command, input=b'toto\n').decode()
	expected = 'toto\n%s\n' % hashstr("toto\n", algo='sha256')

	assert out == expected

def test_sha256_simple_stdin_hash_multiple_arg():
	command = [f'{PROGRAM}', 'sha256', '-q', '-p', '-r']
	out = check_output(command, input=b'toto\n').decode()
	expected = 'toto\n%s\n' % hashstr("toto\n", algo='sha256')

	assert out == expected

def test_sha256_simple_file_hash():
	command = [f'{PROGRAM}', 'sha256', './README.md']
	out = check_output(command).decode()
	expected = 'SHA256 (./README.md) = %s\n' % hashfile('./README.md', algo='sha256')

	assert out == expected

# from subject

def test_sha256_subject_1():
	with open('file', 'w+') as tfile:
		tfile.write('https://www.youtube.com/watch?v=w-5yAtMtrSM\n')
	command = [f'{PROGRAM}', 'sha256', '-q', 'file']
	out = check_output(command).decode()
	expected = (
		'{}\n'
	).format(
		hashfile('file', algo='sha256'),
	)
	os.remove('file')

	assert out == expected

def test_sha256_subject_2():
	with open('file', 'w+') as tfile:
		tfile.write('https://www.youtube.com/watch?v=w-5yAtMtrSM\n')
	command = [f'{PROGRAM}', 'sha', '-sha256', 'file']
	out = check_output(command).decode()
	expected = (
		'SHA256 (file) = {}\n'
	).format(
		hashfile('file', algo='sha256'),
	)
	os.remove('file')

	assert out == expected

def test_sha256_subject_3():
	command = [f'{PROGRAM}', 'sha256', '-s', 'wubba lubba dub dub']
	out = check_output(command).decode()
	expected = (
		'SHA256 ("wubba lubba dub dub") = {}\n'
	).format(
		hashstr('wubba lubba dub dub', algo='sha256'),
	)
	assert out == expected

# ===============================

# =========== tests correction ===========

def test_correction_1_md5():
	command = [f'{PROGRAM}', 'md5']
	out = check_output(command, input=b'is md5("salt") a salted hash? :thonking_face:\n').decode()
	expected = (
		'{}\n'
	).format(
		hashstr('is md5("salt") a salted hash? :thonking_face:\n', algo='md5'),
	)
	assert out == expected

def test_correction_1_sha256():
	command = [f'{PROGRAM}', 'sha256']
	out = check_output(command, input=b'is md5("salt") a salted hash? :thonking_face:\n').decode()
	expected = (
		'{}\n'
	).format(
		hashstr('is md5("salt") a salted hash? :thonking_face:\n', algo='sha256'),
	)
	assert out == expected

def test_correction_2_md5():
	command = [f'{PROGRAM}', 'md5']
	out = check_output(command, input=b'Magic mirror on the wall, think I wanna smash them all?\n').decode()
	expected = (
		'{}\n'
	).format(
		hashstr('Magic mirror on the wall, think I wanna smash them all?\n', algo='md5'),
	)
	assert out == expected

def test_correction_2_sha256():
	command = [f'{PROGRAM}', 'sha256']
	out = check_output(command, input=b'Magic mirror on the wall, think I wanna smash them all?\n').decode()
	expected = (
		'{}\n'
	).format(
		hashstr('Magic mirror on the wall, think I wanna smash them all?\n', algo='sha256'),
	)
	assert out == expected

def test_correction_3_md5():
	command = [f'{PROGRAM}', 'md5']
	out = check_output(command, input=b'Speed up now, Gas Pedal??\n').decode()
	expected = (
		'{}\n'
	).format(
		hashstr('Speed up now, Gas Pedal??\n', algo='md5'),
	)
	assert out == expected

def test_correction_3_sha256():
	command = [f'{PROGRAM}', 'sha256']
	out = check_output(command, input=b'Speed up now, Gas Pedal??\n').decode()
	expected = (
		'{}\n'
	).format(
		hashstr('Speed up now, Gas Pedal??\n', algo='sha256'),
	)
	assert out == expected

# ===============================


# *********** MacOS specific ************

def md5_macos(args, input=None):
	if 'macOS' not in platform.platform():
		return True

	out = check_output(['./ft_ssl', 'md5'] + args.split(), input=input)
	expected = check_output(['md5'] + args.split(), input=input)
	return out == expected

# ----

def test_macos_1():
	assert md5_macos('', input=b'')

def test_macos_2():
	assert md5_macos('', input=b'hello world')

def test_macos_3():
	assert md5_macos('-r ./README.md')

def test_macos_4():
	assert md5_macos('-q ./README.md')

def test_macos_5():
	assert md5_macos('-p', input=b'hello world')
