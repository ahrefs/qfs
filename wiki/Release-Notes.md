QFS version 2.0.

New features
-------------

1. Meta server replication (VR) is the major new feature in this release. Meta
server replication provides automatic meta server fail over. With meta server
replication configured QFS does not have single point of failure.

2. Create exclusive, make directory, remove, remove directory, rename operation
 are guaranteed to be applied only once in the presence of communication
 errors. (Idempotent RPCs).

3. Partial chunk server inventory synchronization.
 The goal is to reduce chunk servers re-connect to the meta server time with
 large chunk inventory.
 Chunk servers  now transmit only list of non-stable / writable chunk IDs, and
 chunk IDs of the RPCs in flight at the time of last disconnect, instead of
 transmitting all "hosted" chunk ids.
 For example for file system with 2 billion chunks full inventory
 synchronization requires around 30 minutes, while partial inventory
 synchronization typically can complete in a few seconds.

4. "Off line" fsck can optionally eimit the same report "on line" fsck, as chunk
 inventory stored in file system meta data (checkpoint, and transaction logs).

Notable changes, and bug fixes
----------------------------------------------

1. New version of QFS protocol with more compact RPC representation to minimize
 network overheads, and CPU utilization.

2. QFS client read and write support larger than 2GB buffers.

3. QFS client write pipelining fixed. Now write path with adequately large
write behind is no longer latency bound.

4. Fixed RS (striped) sparse files recovery.

5. Updated GF complete library version, now includes run time CPU vector features
 detection, and ARM NEON vector instructions support.

6. Fixed sporadic file descriptor close in meta server checkpoint write in case
 when lock file was configured / used.

7. Fixed bug in S3 block delete state machine that appear in the case when more
 one upload ID returned by S3.

8. Fixed re-authentication bug in chunk, meta servers, and client library, that
 resulted connection stalls / timeouts.

9. Changed file delete, by always moving files to dumpster first, then deleting
 file after one lease interval after the most recent read of write lease
 relinquish or expiration.

10. File or directory creation in the dumpster directory is not permitted. Only
permit super user to move file out of dumpster in order to prevent its deletion.

11. File delete scheduled at lower / background priority, avoid delete "bursts"
 in order to maintain low RPCs service latency.

12. Chunk delete queue used with file truncate to reduce chunk delete bursts
 with large files, by scheduling chunk deletes at lower than client requests
 priority.

13. More compact checkpoint and transaction log format, in order to reduce
 disk, network bandwidth, and CPU utilization.

14. Added S3 option that allows to turn off upload ID querying prior to
 S3 block delete, in order to allow to use potentially more cost effective
 external to QFS process of finding and removing possible stale multi part
 uploads.

15. Meta server crypto keys are now always stored in checkpoint and transaction
 log. Configuration parameter metaServer.cryptoKeys.keysFileName is deprecated.

16. WROM mode configuration parameter metaServer.wormMode is deprecated, and has
 no effect. WORM mode is now stored in checkpoint and transaction logs.
 logcompactor has an option to set worm mode when converting checkpoint and
 transaction log into new format. qfsadmin or qfstoggleworm can be used to
 change WORM mode.

17. Retry QFS client directory listing in the case of parse errors in order to
 handle possible network errors.
 
18. Fix integer overflow in IO buffer pool with pool size equal or greater 4GB.
 The problem affects both chunk and meta servers. However, typically, only chunk
 server, if configured with IO buffer pool larger than 4GB, and S3, might use
 enough buffers for the problem to occur.
 

Upgrade from prior releases
---------------------------

Meta server checkpoint and transaction log segments must be converted to new
format. `logcompactor` can be used to convert file system meta data. Please
consult [[Administrator's-Guide]] for details.
