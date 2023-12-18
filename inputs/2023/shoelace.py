def shoelace(tuples_list):
    position, area_a, area_b, total_distance = 0 + 0j, 0, 0, 0
    for direction, distance in tuples_list:
        match direction:
            case 0:
                new_position = position + (1j * distance)
            case 1:
                new_position = position + distance
            case 2:
                new_position = position - (1j * distance)
            case 3:
                new_position = position - distance
        area_a += position.real * new_position.imag
        area_b += position.imag * new_position.real
        total_distance += distance
        position = new_position
    return int((abs(area_a - area_b) / 2) + (total_distance / 2) + 1)

plan = [tuple(line.split()) for line in open('input_18.txt').read().splitlines()]
print(shoelace([('RDLU'.index(direction), int(distance))
                for direction, distance, _ in plan]))
print(shoelace([(int(hex_string[-2]), int(hex_string[2:-2], base=16))
                for _, _, hex_string in plan]))