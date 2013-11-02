


exception ServiceUnavailable {

	1: i32 error_code,
	2: string error_message
}


struct Vector {
	
	1: double x,
	2: double y,
	3: double z,
}

struct Moxel {
	
	1: Vector position,
}

struct Space {
	
	1: list<Moxel> moxels,
}

service Aether {
	
	Space get_moxel_snapshot() throws (1:ServiceUnavailable sunav)
}







