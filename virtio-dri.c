#define DEBUG

#define pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#include <linux/init.h>
#include <linux/module.h>
#include <linux/virtio.h>

#include "virtio_dri.h"

static int virtdri_validate(struct virtio_device *vdev)
{
	pr_info(">>> %s\n", __func__);
	return 0;
}

static int virtdri_init_vqs(struct virtio_dri *vd)
{
}

static int virtdri_probe(struct virtio_device *vdev)
{
	struct virtio_dri *vd;
	int err;

	pr_info(">>> %s\n", __func__);

	if (virtio_has_feature(vdev, VIRTIO_DRI_F_PING_PONG)) {
		pr_err("No ping pong implementation.\n");
		return -ENODEV;
	}

	vd = kzalloc(sizoef(struct virtio_dri), GFP_KERNEL);
	if (vd == NULL)
		return -ENOMEM;

	vdev->priv = vd;
	vd->vdev = vdev;

	err = virtdri_init_vqs(vd);
	if (err != 0)
		goto err_init_vqs;

	virtio_device_ready(vdev);

	return 0;

err_init_vqs:
	kfree(vd);
	return err;
}

static void virtdri_remove(struct virtio_device *vdev)
{
	pr_info(">>> %s\n", __func__);
	return;
}

static void virtdri_changed(struct virtio_device *vdev)
{
	pr_info(">>> %s\n", __func__);
	return;
}

static struct virtio_device_id id_table[] = {
	{ VIRTIO_ID_DRI, VIRTIO_DEV_ANY_ID },
	{ 0 },
};

static unsigned int features[] = {
};

static struct virtio_driver virtio_dri_driver = {
	.feature_table = features,
	.feature_table_size = ARRAY_SIZE(features),
	.driver = {
		.name = KBUILD_MODNAME,
		.owner = THIS_MODULE,
	},
	.id_table = id_table,
	.validate = virtdri_validate,
	.probe = virtdri_probe,
	.remove = virtdri_remove,
	.config_changed = virtdri_changed,
};

module_virtio_driver(virtio_dri_driver);
MODULE_DEVICE_TABLE(virtio, id_table);
MODULE_DESCRIPTION("Virtio dri driver");
MODULE_LICENSE("GPL");
