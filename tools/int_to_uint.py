# one-off script to convert the signed int of samples.h into uint16_t
# this should not be used anymore

for line in open("src/samples.h"):
    if "//" in line:
        samples = line.strip().split(",")
        for i, sample in enumerate(samples):
            try:
                sample = int(sample)
            except ValueError:
                if "};" in sample:
                    number, rest = sample.split("}")
                    number = int(number) + 0x7FFF
                    assert(0 <= number <= 0xFFFF)
                    samples[i] = f"{number}}}{rest}"
                continue

            sample += 0x7FFF
            assert(0 <= sample <= 0xFFFF)
            sample = str(sample)
            samples[i] = sample
        print(', '.join(samples))
    else:
        print(line.strip())
