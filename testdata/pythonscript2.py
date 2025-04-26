import random

# Function to create partially sorted file
def create_partially_sorted_file(filename, num_elements, sorted_sections=5, shuffle_fraction=0.2):
    # Create a list of random values between 1 and 1000
    data = [random.randint(1, 1000) for _ in range(num_elements)]
    
    # Introduce sorted sections within the data
    section_size = num_elements // sorted_sections
    
    for i in range(sorted_sections):
        start_index = i * section_size
        end_index = start_index + section_size if (i + 1) * section_size <= num_elements else num_elements
        data[start_index:end_index] = sorted(data[start_index:end_index])
    
    # Shuffle a fraction of the data to introduce unsorted regions
    shuffle_size = int(num_elements * shuffle_fraction)
    shuffle_indices = random.sample(range(num_elements), shuffle_size)
    for idx in shuffle_indices:
        data[idx] = random.randint(1, 1000)

    # Write the partially sorted data to a file
    with open(filename, 'w') as f:
        for value in data:
            f.write(f"{value}\n")

# Example usage
create_partially_sorted_file("data_100_partially_sorted.txt", 100)  # 1000 total values with partial sorting
