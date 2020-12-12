#include "raw_handler.h"
#include "part/mbr.h"

raw_handler::raw_handler(FILE* fp): handler(fp)
{
    fseek(this->fp, 0, SEEK_SET);

    char boot[512];
    fread(boot, 512, 1, fp);

    auto* mbr = (mbr_t*)boot;

    // GPT partition
    if(mbr->partitions[0].part_type == 0xEE) {
        // TODO
    } else {
        for(int i = 0; i < 4; i++) {
            const mbr_part_t& part = mbr->partitions[i];

            if(part.num_sectors == 0)
                break;

            partitions[i] = {
                    .b_start = part.lba_first * 512,
                    .b_end = (part.lba_first + part.num_sectors) * 512
            };
        }
    }
}

int raw_handler::read(int part, char* buffer, uint64_t amt, uint64_t pos)
{
    if(!is_valid(part))
        return -1;

    uint64_t p_start = partitions[part].b_start + pos;

    if(p_start >= partitions[part].b_end)
        return -1;

    uint64_t p_amt = p_start + amt > partitions[part].b_end ?
            partitions[part].b_end - p_start : amt;

    fseek(this->fp, p_start, SEEK_SET);
    return fread(buffer, p_amt, 1, fp);
}

int raw_handler::write(int part, char* buffer, uint64_t amt, uint64_t pos)
{
    if(!is_valid(part))
        return -1;

    uint64_t p_start = partitions[part].b_start + pos;

    if(p_start >= partitions[part].b_end)
        return -1;

    uint64_t p_amt = p_start + amt > partitions[part].b_end ?
                     partitions[part].b_end - p_start : amt;

    fseek(this->fp, p_start, SEEK_SET);
    return fwrite(buffer, p_amt, 1, fp);
}

bool raw_handler::is_valid(int part)
{
    return partitions.find(part) != partitions.end();
}
